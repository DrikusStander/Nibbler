#!/bin/bash
brew list pkg-config &>/dev/null || brew install pkg-config
brew list sdl2 &>/dev/null || brew install sdl2
brew list sdl2_ttf &>/dev/null || brew install sdl2_ttf