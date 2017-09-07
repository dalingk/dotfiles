syntax enable
set tabstop=4
set softtabstop=4
set expandtab
set number
set showcmd
set cursorline
filetype indent on
set wildmenu
set lazyredraw
set showmatch

set hlsearch

set foldenable
set foldlevelstart=10
set foldnestmax=10
set foldmethod=indent

set colorcolumn=80
highlight ColorColumn ctermbg=4
" Write with sudo hack
cmap w!! w !sudo tee > /dev/null %
