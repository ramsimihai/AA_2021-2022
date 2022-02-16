#!/bin/bash


readarray -d '' entries < <(printf '%s\0' *.in | sort -zV)
for entry in "${entries[@]}"; do
  cat "$entry" | head -1 | cut -d' ' -f2
done
