#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import re
import yaml
import logging
import datetime
from pathlib import Path

def setup_logging(log_dir=None):
    """로깅 설정을 초기화합니다."""
    if log_dir is None:
        # 스크립트 디렉토리 내에 logs 폴더 생성
        script_dir = Path(__file__).parent
        log_dir = script_dir / 'logs'
    
    # 로그 디렉토리가 없으면 생성
    log_dir.mkdir(exist_ok=True)
    
    # 로그 파일명에 타임스탬프 추가
    timestamp = datetime.datetime.now().strftime('%Y%m%d_%H%M%S')
    log_file = log_dir / f'mkdocs_nav_{timestamp}.log'
    
    # 로그 포맷 설정
    logging.basicConfig(
        level=logging.INFO,
        format='%(asctime)s - %(levelname)s - %(message)s',
        handlers=[
            logging.FileHandler(log_file, encoding='utf-8'),
            logging.StreamHandler()  # 콘솔에도 출력
        ]
    )
    
    return log_file

def sanitize_url(title):
    """URL에 안전하게 사용할 수 있도록 제목에서 문제가 되는 문자를 제거합니다."""
    # URL에 문제가 될 수 있는 문자들을 제거하거나 변환
    # 공백은 하이픈으로 변환
    url = title.replace(' ', '-')
    # + 기호는 plus로 변환
    url = url.replace('+', 'plus')
    # 기타 특수문자 제거
    url = re.sub(r'[<>:"/\\|?*]', '-', url)
    # 다중 하이픈을 단일 하이픈으로 변환
    url = re.sub(r'-+', '-', url)
    # 앞뒤 하이픈 제거
    url = url.strip('-')
    
    return url.lower()  # 소문자로 반환

def check_problematic_files(directory):
    """문제가 될 수 있는 파일들을 스캔합니다."""
    problematic_files = []
    directory = Path(directory)
    
    # 모든 마크다운 파일 스캔
    for path in directory.glob('**/*.md'):
        # docs 디렉토리 내의 파일은 제외
        if 'docs' in path.parts and path.parts.index('docs') == len(path.parts) - 2:
            continue
        
        filename = path.name
        
        # 문제가 될 수 있는 패턴 확인
        if (
            ' ' in filename or  # 공백 포함
            '+' in filename or  # + 기호 포함
            any(c in filename for c in '<>:"/\\|?*')  # 기타 위험한 문자 포함
        ):
            # 프로젝트 루트 기준 상대 경로로 변환
            rel_path = os.path.relpath(path, directory).replace('\\', '/')
            problematic_files.append((rel_path, path.stem))
    
    return problematic_files

def load_mkdocs_config(config_path):
    """MkDocs 설정 파일을 로드합니다."""
    with open(config_path, 'r', encoding='utf-8') as f:
        return yaml.safe_load(f)

def save_mkdocs_config(config_path, config):
    """MkDocs 설정 파일을 저장합니다."""
    with open(config_path, 'w', encoding='utf-8') as f:
        yaml.dump(config, f, allow_unicode=True, sort_keys=False)

def find_or_create_nav_entry(nav, path_parts, title, url):
    """Nav 트리에서 적절한 위치를 찾거나 생성하여 항목을 추가합니다."""
    if not path_parts:  # 기본 레벨에 추가
        # 이미 존재하는지 확인
        for entry in nav:
            if isinstance(entry, dict) and url in entry.values():
                logging.info(f"항목이 이미 존재합니다: {title} -> {url}")
                return False
        
        # 존재하지 않으면 추가
        nav.append({title: url})
        logging.info(f"항목 추가됨: {title} -> {url}")
        return True
    
    # 하위 디렉토리 처리
    current_dir = path_parts[0]
    remaining_parts = path_parts[1:]
    
    # 해당 디렉토리 항목을 찾음
    for entry in nav:
        if isinstance(entry, dict) and current_dir in entry:
            # 재귀적으로 하위 항목 처리
            if not isinstance(entry[current_dir], list):
                entry[current_dir] = []
            return find_or_create_nav_entry(entry[current_dir], remaining_parts, title, url)
    
    # 디렉토리 항목이 없으면 생성
    new_entry = {current_dir: []}
    nav.append(new_entry)
    logging.info(f"디렉토리 추가됨: {current_dir}")
    
    # 재귀적으로 하위 항목 처리
    return find_or_create_nav_entry(new_entry[current_dir], remaining_parts, title, url)

def update_mkdocs_nav(config_path, problematic_files, root_dir):
    """MkDocs 설정 파일의 nav 섹션을 업데이트합니다."""
    config = load_mkdocs_config(config_path)
    
    # nav 섹션이 없으면 생성
    if 'nav' not in config:
        config['nav'] = []
    
    changes_made = False
    
    for rel_path, title in problematic_files:
        # 파일이 실제로 존재하는지 확인
        file_path = os.path.join(root_dir, rel_path)
        if not os.path.exists(file_path):
            logging.warning(f"파일이 존재하지 않아 건너뜁니다: {rel_path}")
            continue
        
        # 파일의 경로를 분해
        path_parts = os.path.dirname(rel_path).split('/')
        # 빈 경로 항목 제거
        path_parts = [p for p in path_parts if p]
        
        # 변경된 경우 True 반환
        if find_or_create_nav_entry(config['nav'], path_parts, title, rel_path):
            changes_made = True
    
    # 변경사항이 있으면 파일 저장
    if changes_made:
        save_mkdocs_config(config_path, config)
        logging.info(f"MkDocs 설정 파일이 업데이트되었습니다: {config_path}")
    else:
        logging.info("변경사항이 없습니다.")
    
    return changes_made

def verify_mkdocs_build(config_path):
    """MkDocs 빌드를 검증합니다."""
    import subprocess
    
    try:
        result = subprocess.run(
            ["mkdocs", "build", "-f", config_path, "--strict"],
            capture_output=True,
            text=True,
            check=False
        )
        
        if result.returncode == 0:
            logging.info("MkDocs 빌드 검증 성공!")
            return True, result.stdout
        else:
            logging.error(f"MkDocs 빌드 검증 실패: {result.stderr}")
            return False, result.stderr
    except Exception as e:
        logging.error(f"MkDocs 빌드 검증 중 오류 발생: {e}")
        return False, str(e)

def main():
    import argparse
    
    parser = argparse.ArgumentParser(description='MkDocs nav 설정을 자동으로 업데이트합니다.')
    parser.add_argument('--root-dir', type=str, default='..',
                        help='프로젝트 루트 디렉토리 (default: ..)')
    parser.add_argument('--config', type=str, default='./mkdocs.yml',
                        help='MkDocs 설정 파일 경로 (default: ./mkdocs.yml)')
    parser.add_argument('--verify-build', action='store_true',
                        help='MkDocs 빌드 검증 수행')
    parser.add_argument('--log-dir', type=str, help='로그 파일을 저장할 디렉토리 경로')
    
    args = parser.parse_args()
    
    # 로그 설정
    log_dir = None
    if args.log_dir:
        log_dir = Path(args.log_dir)
    
    log_file = setup_logging(log_dir)
    logging.info(f"로그 파일: {log_file}")
    
    # 절대 경로로 변환
    root_dir = os.path.abspath(args.root_dir)
    config_path = os.path.abspath(args.config)
    
    logging.info(f"프로젝트 루트 디렉토리: {root_dir}")
    logging.info(f"MkDocs 설정 파일: {config_path}")
    
    # 문제가 될 수 있는 파일 스캔
    logging.info("문제가 될 수 있는 파일 스캔 중...")
    problematic_files = check_problematic_files(root_dir)
    logging.info(f"문제가 될 수 있는 파일 {len(problematic_files)}개 발견")
    
    for rel_path, title in problematic_files:
        logging.info(f"  - {rel_path}")
    
    # MkDocs nav 섹션 업데이트
    logging.info("MkDocs nav 섹션 업데이트 중...")
    changes_made = update_mkdocs_nav(config_path, problematic_files, root_dir)
    
    # 빌드 검증 (옵션)
    if args.verify_build:
        logging.info("MkDocs 빌드 검증 중...")
        success, log = verify_mkdocs_build(config_path)
        
        if success:
            logging.info("빌드 검증 성공!")
        else:
            logging.error("빌드 검증 실패. 자세한 내용은 로그 참조.")
    
    print(f"처리 완료. 로그 파일: {log_file}")

if __name__ == "__main__":
    main()
