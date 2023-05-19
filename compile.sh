emcc --bind -O3 \
  components/element/Element.cpp \
  components/style/Style.cpp \
  components/state/State.cpp \
  components/button/Button.cpp \
  components/flex/Flex.cpp \
  components/input/Input.cpp \
  index.cpp \
  -o index.js