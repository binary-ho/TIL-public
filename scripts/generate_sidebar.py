#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import re
import urllib.parse
from pathlib import Path
import logging
import datetime

# 로깅 설정
def setup_logging():
    """로깅 설정을 초기화합니다."""
    script_dir = Path(__file__).parent
    log_dir = script_dir / 'logs'
    
    # 로그 디렉토리가 없으면 생성
    log_dir.mkdir(exist_ok=True, parents=True)
    
    # 로그 파일명에 타임스탬프 추가
    timestamp = datetime.datetime.now().strftime('%Y%m%d_%H%M%S')
    log_file = log_dir / f'sidebar_generation_{timestamp}.log'
    
    # 로그 포맷 설정
    logging.basicConfig(
        level=logging.INFO,
        format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
        handlers=[
            logging.FileHandler(log_file, encoding='utf-8'),
            logging.StreamHandler()
        ]
    )
    return logging.getLogger('sidebar_generator')

def get_markdown_files(root_dir, exclude_paths=None):
    """
    주어진 디렉토리에서 모든 마크다운 파일을 찾습니다.
    
    Args:
        root_dir (str): 스캔할 루트 디렉토리
        exclude_paths (list): 제외할 경로 목록 (기본값: None)
    
    Returns:
        list: 마크다운 파일 경로 목록
    """
    if exclude_paths is None:
        exclude_paths = ['.git', 'node_modules', '.github', 'scripts/logs']
    
    markdown_files = []
    
    for root, dirs, files in os.walk(root_dir):
        # 제외 디렉토리 필터링
        dirs[:] = [d for d in dirs if not any(ex in os.path.join(root, d) for ex in exclude_paths)]
        
        for file in files:
            if file.lower().endswith('.md') and file != '_sidebar.md' and file != 'README.md':
                file_path = os.path.join(root, file)
                rel_path = os.path.relpath(file_path, root_dir)
                markdown_files.append(rel_path)
    
    return sorted(markdown_files)

def url_encode_path(path):
    """
    URL에서 사용하기 위해 경로를 인코딩합니다.
    공백과 특수문자를 처리합니다.
    
    Args:
        path (str): 인코딩할 경로
    
    Returns:
        str: 인코딩된 경로
    """
    # 경로 구성요소를 개별적으로 인코딩
    parts = path.split('/')
    encoded_parts = [urllib.parse.quote(part) for part in parts]
    return '/'.join(encoded_parts)

def extract_title(file_path, root_dir):
    """
    마크다운 파일에서 제목을 추출합니다.
    파일의 첫 번째 헤더가 제목이라고 가정합니다.
    
    Args:
        file_path (str): 마크다운 파일 경로
        root_dir (str): 루트 디렉토리
    
    Returns:
        str: 추출된 제목 또는 파일 이름
    """
    full_path = os.path.join(root_dir, file_path)
    try:
        with open(full_path, 'r', encoding='utf-8') as f:
            content = f.read()
            
            # # 또는 ## 형식의 헤더 찾기
            header_match = re.search(r'^#\s+(.+)$', content, re.MULTILINE)
            if header_match:
                return header_match.group(1).strip()
            
            # 파일 이름에서 확장자 제거하여 사용
            return os.path.splitext(os.path.basename(file_path))[0]
    except Exception as e:
        logger.warning(f"파일 '{file_path}' 처리 중 오류 발생: {e}")
        return os.path.splitext(os.path.basename(file_path))[0]

def organize_by_directory(markdown_files, root_dir):
    """
    마크다운 파일을 디렉토리 구조로 정리합니다.
    
    Args:
        markdown_files (list): 마크다운 파일 경로 목록
        root_dir (str): 루트 디렉토리
    
    Returns:
        dict: 디렉토리 구조로 정리된 파일 딕셔너리
    """
    directory_structure = {}
    
    for file_path in markdown_files:
        path_parts = file_path.split(os.sep)
        current_level = directory_structure
        
        # 디렉토리 계층 구조를 만들고 탐색
        for i, part in enumerate(path_parts[:-1]):
            if part not in current_level:
                current_level[part] = {}
            current_level = current_level[part]
        
        # 파일 추가
        file_name = path_parts[-1]
        title = extract_title(file_path, root_dir)
        current_level[file_name] = {
            'title': title,
            'path': file_path
        }
    
    return directory_structure

def generate_sidebar_content(directory_structure, level=0, current_path=''):
    """
    디렉토리 구조에서 사이드바 마크다운 콘텐츠를 생성합니다.
    
    Args:
        directory_structure (dict): 디렉토리 구조 딕셔너리
        level (int): 현재 들여쓰기 레벨
        current_path (str): 현재 경로
    
    Returns:
        str: 생성된 사이드바 마크다운 콘텐츠
    """
    sidebar_content = []
    indent = '  ' * level
    
    # 디렉토리와 파일 구분
    directories = {}
    files = {}
    
    for key, value in directory_structure.items():
        if isinstance(value, dict) and not any(k in ['title', 'path'] for k in value.keys()):
            directories[key] = value
        else:
            files[key] = value
    
    # 디렉토리 먼저 처리
    for dir_name, contents in sorted(directories.items()):
        # 디렉토리 이름을 더 읽기 쉽게 표시
        display_name = dir_name.replace('-', ' ').replace('_', ' ')
        sidebar_content.append(f"{indent}* **{display_name}**")
        
        # 재귀적으로 하위 항목 처리
        new_path = os.path.join(current_path, dir_name) if current_path else dir_name
        sub_content = generate_sidebar_content(contents, level + 1, new_path)
        sidebar_content.append(sub_content)
    
    # 파일 처리
    for file_name, file_info in sorted(files.items()):
        if isinstance(file_info, dict) and 'title' in file_info and 'path' in file_info:
            title = file_info['title']
            path = file_info['path']
            encoded_path = url_encode_path(path)
            sidebar_content.append(f"{indent}* [{title}](/{encoded_path})")
    
    return '\n'.join(sidebar_content)

def save_sidebar(content, output_file):
    """
    생성된 사이드바 콘텐츠를 파일로 저장합니다.
    
    Args:
        content (str): 사이드바 마크다운 콘텐츠
        output_file (str): 출력 파일 경로
    """
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(content)
    logger.info(f"사이드바 파일이 '{output_file}'에 저장되었습니다.")

def main():
    """메인 함수"""
    root_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    output_file = os.path.join(root_dir, '_sidebar.md')
    
    logger.info(f"마크다운 파일 스캔 중: {root_dir}")
    markdown_files = get_markdown_files(root_dir)
    logger.info(f"{len(markdown_files)}개의 마크다운 파일을 찾았습니다.")
    
    logger.info("디렉토리 구조로 정리 중...")
    directory_structure = organize_by_directory(markdown_files, root_dir)
    
    logger.info("사이드바 콘텐츠 생성 중...")
    # 홈 링크 추가
    sidebar_content = "* [홈](/)\n\n"
    sidebar_content += generate_sidebar_content(directory_structure)
    
    logger.info("사이드바 파일 저장 중...")
    save_sidebar(sidebar_content, output_file)
    
    logger.info("사이드바 생성 완료!")

if __name__ == "__main__":
    logger = setup_logging()
    main()
