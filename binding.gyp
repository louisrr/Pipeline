{
  "targets": [
    {
      "target_name": "addon",
      "sources": [
        "src/addon.cpp",
        "src/Pipeline.cpp"
      ],
      "include_dirs": [
        "<!(node -e \"require('node-addon-api').include\")",
        "src"
      ],
      "dependencies": [
        "<!(node -e \"require('node-addon-api').gyp\")"
      ],
      "cflags_cc": [
        "-std=c++17"
      ],
      "link_settings": {
        "libraries": []
      }
    }
  ]
}
