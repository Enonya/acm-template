
func Format()
	exec ':%s/){/) {/g'
	exec ':%s/,/, /g'
	exec ':%s/;/; /g'
	exec ':%s/inline //g'
	exec ':%s/register //g'
	exec ':%s/=/ = /g'
	exec ':%s/ =  = / == /g'
	exec ':%s/< = / <= /g'
	exec ':%s/> = / >= /g'
	exec ':%s/! = / != /g'
	exec ':%s/<</ << /g'
	exec ':%s/>>/ >> /g'
	exec ':%s/+/ + /g'
	exec ':%s/-/ - /g'
	exec ':%s/ +  + / ++ /g'
	exec ':%s/ -  - / -- /g'
	exec ':%s/*/ * /g'
	exec ':%s/\// \/ /g'
endfunc
nmap <F8> :call Format()<CR>
