#!/bin/bash

comm=$1

git add .
git commit -m "$comm"
git push
