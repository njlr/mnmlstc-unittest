import os

project = 'MNMLSTC Unittest'
copyright = '2013, MNMSLTC'

version = '0.1'
release = '0.1'

html_theme = 'default' if os.environ.get('READTHEDOCS', None) else 'nature'

exclude_patterns = ['_build']
templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'
todo_include_todos = True
extensions = ['sphinx.ext.todo']
