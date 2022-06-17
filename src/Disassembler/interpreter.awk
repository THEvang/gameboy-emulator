BEGIN {
	print "switch(opcode) {" }
{
	printf "case %s:\n", ($1)
	printf "printf(\"%s\t%s\t%s\\n\");\n", $1, $2, $3
	printf "pos += %s\n;", $4
	printf "break;\n"	
}
END{print "}"}


