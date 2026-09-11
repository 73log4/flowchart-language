
## Welcome to the FlowChart language !


#### Language syntax:

General:
- All variables are strings
- Lines end in `;` or `:`
- Variable names use python convention

Commands:
```txt
# init - initialize a variable  with string
[var] = [string];

# print - print to output stream the variables content or the string
print [var\string];

# take input from input stream into variable
input [var];

# exec - execute a bash command with possible inputs as variables
exec "bash_cmd -i -l arg1 {var1} {var2}"

# if - check if variable satisfies a regex, must contain an else
if [var] ? [regex]:
	...
else:
	...
	
# jump - jump to line idetifier
[[line_iden]] ...
...
jump line_iden;

# switch - switch case, must contain an else
switch [var]:
	[var] = [string1]: ...
	[var] = [string2]: ...
	else: ...
	
# exit - end execution of code
exit;

```