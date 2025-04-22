#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import logging
import datetime
from pathlib import Path
import argparse

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
    log_file = log_dir / f'filename_edge_cases_{timestamp}.log'
    
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

def fix_trailing_spaces(directory, dry_run=False):
    """파일명 끝의 공백을 제거합니다. nav 설정으로 해결할 수 없는 문제입니다."""
    directory = Path(directory)
    fixed_files = []
    
    # 모든 마크다운 파일 스캔
    for path in directory.glob('**/*.md'):
        # docs 디렉토리 내의 파일은 제외
        if 'docs' in path.parts and path.parts.index('docs') == len(path.parts) - 2:
            continue
        
        filename = path.name
        dirname = path.parent
        
        # 파일명 끝에 공백이 있는지 확인
        stem = path.stem
        if stem.rstrip() != stem:
            new_stem = stem.rstrip()
            new_filename = new_stem + path.suffix
            new_path = dirname / new_filename
            
            logging.info(f"파일명 끝 공백 발견: {path}")
            logging.info(f"변경할 파일명: {new_path}")
            
            if not dry_run:
                try:
                    os.rename(path, new_path)
                    logging.info(f"파일명 변경 성공: {path} -> {new_path}")
                    fixed_files.append((str(path), str(new_path)))
                except Exception as e:
                    logging.error(f"파일명 변경 실패: {path}, 오류: {e}")
            else:
                logging.info(f"DRY-RUN 모드: 파일명 변경 건너뜀")
                fixed_files.append((str(path), str(new_path)))
    
    return fixed_files

def main():
    parser = argparse.ArgumentParser(description='nav 설정으로 해결할 수 없는 파일명 문제를 수정합니다.')
    parser.add_argument('--root-dir', type=str, default='..',
                        help='프로젝트 루트 디렉토리 (default: ..)')
    parser.add_argument('--dry-run', action='store_true',
                        help='실제 변경 없이 무엇이 변경될지 확인')
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
    
    logging.info(f"프로젝트 루트 디렉토리: {root_dir}")
    logging.info(f"DRY-RUN 모드: {args.dry_run}")
    
    # 파일명 끝 공백 수정
    fixed_files = fix_trailing_spaces(root_dir, args.dry_run)
    
    if fixed_files:
        logging.info(f"{len(fixed_files)}개 파일의 끝 공백 수정 완료")
        for old_path, new_path in fixed_files:
            print(f"{old_path} -> {new_path}")
    else:
        logging.info("수정할 파일이 없습니다.")
    
    print(f"처리 완료. 로그 파일: {log_file}")

if __name__ == "__main__":
    main()
