# node-bgfx

BGFX bindings to node.js

#### Quickstart

```bash
npm run generate  # Regenerate C++ bindings
npm install       # Build native bindings
npm lint          # Perform ESLint check
npm test          # Run Jest unit tests.
```

#### Notes

* Fix for the library name used by bgfx on OSX:
  ```
  $ install_name_tool -id "@rpath/libbgfx-shared-libRelease.dylib" ./deps/bgfx/bin/darwin/x64/libbgfx-shared-libRelease.dylib
  ```
