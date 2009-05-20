#!/bin/bash

cd ./docs
gtkdoc-scan --module=SPRY --source-dir=../src --output-dir=.
gtkdoc-mktmpl --module=SPRY
gtkdoc-mkdb --module=SPRY --source-dir=../src --tmpl-dir=tmpl --output-format=xml --main-sgml-file=SPRY-docs.sgml
gtkdoc-mkhtml SPRY SPRY-docs.sgml

rm -rf *.txt *.xml *sgml* *.dev* xml* tmpl* *.types *.bak

cd ..
