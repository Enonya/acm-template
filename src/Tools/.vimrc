syntax on
color xterm16

set ts=4 sts=4 sw=4 ai
set wildmenu nocompatible nu rnu ruler mouse=a
set timeoutlen=666 ttimeoutlen=0 backup swapfile undofile
set ar acd backspace=indent,eol,start foldmethod=marker
set encoding=utf-8

nmap F :e ./<CR>
nmap <leader>n :tabnew<CR>
nmap <leader>tc :term<CR>

inoremap [ []<Esc>i
inoremap {<CR> {}<ESC>i<CR><ESC>O
inoremap ( ()<Esc>i
inoremap ' ''<Esc>i
inoremap " ""<Esc>i
