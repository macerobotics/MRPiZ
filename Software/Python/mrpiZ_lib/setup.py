#!/usr/bin/env python
# -*- coding: utf-8 -*-
 
from setuptools import setup, find_packages
 
# notez qu'on import la lib
# donc assurez-vous que l'importe n'a pas d'effet de bord
import mrpiZ_lib
 
setup(
 
    # name lib
    name='mrpiZ_lib',
 
    # version
    version=mrpiZ_lib.__version__,
 
    # Liste les packages à insérer dans la distribution
    packages=find_packages(),
 
    # Name
    author="Mace Robotics",
 
    # email
    author_email="contact@macerobotics.com",
 
    # description lib 
    description="MRPiZ python library",
 
    # lib presentation
    long_description=open('README.md').read(),
 
    # Active la prise en compte du fichier MANIFEST.in
    include_package_data=True,
 
    # URL github
    url='xxx',
 
    classifiers=[
        "Programming Language :: Python",
        "Development Status :: 1 - Planning",
        "License :: OSI Approved",
        "Natural Language :: French",
        "Operating System :: OS Independent",
        "Programming Language :: Python :: 2.7",
        "Topic :: Communications",
    ],
 
    entry_points = {
        'console_scripts': [
            'proclame-sm = mrpi1_lib.core:proclamer',
        ],
    },

    license="Licence MIT",
)