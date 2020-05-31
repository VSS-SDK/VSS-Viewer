#!/bin/bash

# Entrypoint: The Viewer Binary
./build/vss-viewer | tee log.txt

# Debug - Should be removed later
while true; do sleep 1000; done

