from setuptools import setup, find_packages

with open('requirements.txt') as file:
    requirements = file.readlines()

setup(
    name='brainduck_interpreter',
    version='v1',
    packages=find_packages(),
    url='',
    author='rakRandom',
    description='Brainfuck language interpreter',
    install_requires=requirements
)
