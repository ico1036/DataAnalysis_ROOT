#!/bin/bash

#.L sample/sampletest.C+  ->> Error

root <<EOF
gSystem->cd("sample");
gSystem->CompileMacro("sampletest.C")
EOF
