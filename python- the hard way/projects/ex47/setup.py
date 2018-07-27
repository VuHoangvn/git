try:
	from setuptools import setup
except ImportError:
	from distutils.core import setup
	
config = {
	'description': 'My project',
	'author': 'My Name',
	'url': 'URL to get it at.',
	'author_email': My email',
	'version': '0.1',
	'install_requires': ['nose'],
	'packages': ['ex47'],
	'scripts': [],
	'name': 'projectname'
}