(($2 == "macro" || $2 == "enumerator") && $1 ~ /^(vc|VC|CLONE)/ &&
	$1 !~ /^VC_ATTR_/) {
	printf "  PyModule_AddIntConstant(mod, \"%s\", %s);\n", $1, $1
}
