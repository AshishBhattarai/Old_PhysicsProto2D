" Ale
let g:ale_c_build_dir = '/home/tear/Documents/Cpp/OpenGL/2DPhysicsProto/build/'
let g:ale_cpp_build_dir = '/home/tear/Documents/Cpp/OpenGL/2DPhysicsProto/build/'
let g:ale_cpp_clangtidy_options = '-std=c++17 -Isrc/'

" Clang-Format
let g:clang_format#style_options = {
            \ "BasedOnStyle" : "llvm",
            \ "BreakBeforeBraces" : "Attach",
            \ "UseTab" : "Never",
            \ "TabWidth" : 2,
            \ "IndentWidth" : 2,
            \ "ColumnLimit" : 100,
            \ "AccessModifierOffset" : -2,
            \ "AllowShortIfStatementsOnASingleLine" : "true",
            \ "AllowShortFunctionsOnASingleLine" : "true",
            \}

" Style
set colorcolumn=100
