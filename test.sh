#!/bin/bash

if [ -z "$1" ]; then
  DEMO_PATH=./demo
  if [ ! -e "${DEMO_PATH}" ]; then
    if [ -e ./demo.exe ]; then
      DEMO_PATH=./demo.exe
    fi
  fi
else
  DEMO_PATH="$1"
fi

if [ ! -e "${DEMO_PATH}" ]; then
  echo Cannot find executable.
  exit 1
fi

shopt -s nullglob
for jpeg in test-images/*.jpg; do
  ACTUAL_OUTPUT=/tmp/$(basename $jpeg).actual
  DIFF_TEXT=/tmp/diff.txt

  ${DEMO_PATH} $jpeg > "${ACTUAL_OUTPUT}"
  diff $jpeg.expected "${ACTUAL_OUTPUT}" > "${DIFF_TEXT}"
  rm "${ACTUAL_OUTPUT}"
  if [[ -s "${DIFF_TEXT}" ]] ; then
    echo "FAILED ON $jpeg"
    cat "${DIFF_TEXT}"
    HAS_FAILURE=true
  else
    echo "PASS $jpeg"
  fi
  rm "${DIFF_TEXT}"
done

if [ -n "$HAS_FAILURE" ]; then
  echo "ERROR One or more tests failed"
  exit 2
fi