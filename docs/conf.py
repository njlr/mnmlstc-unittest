import cloud_sptheme as csp
import os

project = 'MNMLSTC Unittest'
copyright = '2013, MNMSLTC'

version = '1.0'
release = '1.0'

html_static_path = ['static']
html_theme_path = [csp.get_theme_dir()]
html_theme = 'cloud'
html_logo = os.path.join('static', 'unittest-logo.png')


exclude_patterns = ['_build']
templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'

extensions = ['cloud_sptheme.ext.issue_tracker', 'sphinx.ext.todo']

issue_tracker_url = 'https://github.com/mnmlstc/unittest/issues'
todo_include_todos = True
