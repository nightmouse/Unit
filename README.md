# Unit #
- - -

## Explanation ##
The idea behind this project is to create a unit testing frame work with a minimal amout of overhead.

## Building ##
1. Pull the code.
2. Execute `make run` from the top level directory.

* 'make run' will compile all sources and run a few built in tests.
* 'make valrun' will run valgrind on the resulting executable

## UnitTest Command Line Arguments ##
<table>
<tr>
<td><code>--help</code></td><td>Display command line option help</td>
</tr>

<tr>
<td><code>--run=t1,t2,t3</code></td><td>Specify which tests to run</td>
</tr>

<tr>
<td><code>--exclude=t1,t2,t3</code></td><td>Specify which tests <u>not</u> to run</td>
<tr>

<tr>
<td><code>--json=file</code></td><td>Store the test result in file with a json format</td>
</tr>
</table>


## TestNames ##
Test names can be registered in a somewhat hierarchical way. For instance, if there are three tests under "Foo", To exclude all of them execute the command line:

`UnitTest --exclude=Foo`

 Each test must have a uniqe name.

## Template ##
A template unit test, template.cpp, is available in the top level directory.
