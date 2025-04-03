# Grammar and Types

JavaScript borrows most of its syntax from Java, C, and C++, but it has also been influenced by Awk, Perl, and Python.

JavaScript is case-sensitive and uses the Unicode character set. For example, the word Früh (which means "early" in German) could be used as a variable name.

```JS
const Früh = "foobar";
```

But, the variable früh is not the same as Früh because JavaScript is case sensitive.

In JavaScript, instructions are called statements and are separated by semicolons (;).

A semicolon is not necessary after a statement if it is written on its own line. But if more than one statement on a line is desired, then they must be separated by semicolons.

>|**Note**:|
>|---------|
>|ECMAScript also has rules for automatic insertion of semicolons (ASI) to end statements. (For more information, see the detailed reference about JavaScript's lexical grammar.)|

It is considered best practice, however, to always write a semicolon after a statement, even when it is not strictly needed. This practice reduces the chances of bugs getting into the code.

The source text of JavaScript script gets scanned from left to right, and is converted into a sequence of input elements which are tokens, control characters, line terminators, comments, or whitespace. (Spaces, tabs, and newline characters are considered whitespace.)

## Comments

The syntax of comments is the same as in C++ and in many other languages:

```JS
// a one line comment

/* this is a longer,
 * multi-line comment
 */
```

You can't nest block comments. This often happens when you accidentally include a */ sequence in your comment, which will terminate the comment.

```JS
/* You can't, however, /* nest comments */ SyntaxError */
```

In this case, you need to break up the */ pattern. For example, by inserting a backslash:

```JS
/* You can /* nest comments *\/ by escaping slashes */
```

Comments behave like whitespace, and are discarded during script execution.

>|**Note:**|
>|---------|
>|You might also see a third type of comment syntax at the start of some JavaScript files, which looks something like this: `#!/usr/bin/env node`.|
>|This is called hashbang comment syntax, and is a special comment used to specify the path to a particular JavaScript engine that should execute the script. See Hashbang comments for more details.|

## Declaration

JavaScript has three kinds of variable declarations.

1. var - Declares a variable, optionally initializing it to a value.
2. let - Declares a block-scoped, local variable, optionally initializing it to a value.
3. const - Declares a block-scoped, read-only named constant.

### Variables

You use variables as symbolic names for values in your application. The names of variables, called [identifiers](https://developer.mozilla.org/en-US/docs/Glossary/Identifier), conform to certain rules.
A JavaScript identifier usually starts with a letter, underscore (_), or dollar sign ($). Subsequent characters can also be digits (0 – 9). Because JavaScript is case sensitive, letters include the characters A through Z (uppercase) as well as a through z (lowercase).

You can use most Unicode letters such as å and ü in identifiers. (For more details, see the [lexical grammar](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Lexical_grammar) reference.) You can also use [Unicode escape sequences](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Lexical_grammar#string_literals) to represent characters in identifiers.

Some examples of legal names are `Number_hits`, `temp99`, `$credit`, and `_name`.

#### Declaring Variables

You can declare a variable in two ways:

- With the keyword `var`. For example, `var x = 42`. This syntax can be used to declare both local and global variables, depending on the execution context.

- With the keyword `const` or `let`. For example, `let y = 13`. This syntax can be used to declare a block-scope local variable. (See Variable scope below.)

You can declare variables to unpack values using the destructuring syntax. For example, `const { bar } = foo`. This will create a variable named bar and assign to it the value corresponding to the key of the same name from our object `foo`.

Variables should always be declared before they are used. JavaScript used to allow assigning to undeclared variables, which creates an undeclared global variable. This is an error in strict mode and should be avoided altogether.

#### Declaration And Initialization

In a statement like `let x = 42`, the `let x` part is called a declaration, and the `= 42` part is called an initializer. The declaration allows the variable to be accessed later in code without throwing a *`ReferenceError`*, while the initializer assigns a value to the variable. In `var` and `let` declarations, the initializer is optional. If a variable is declared without an initializer, it is assigned the value undefined.

```JS
let x;
console.log(x); //logs "undefined"
```

In essence, `let x = 42` is equivalent to `let x; x = 42`.

`const` declarations always need an initializer, because they forbid any kind of assignment after declaration, and implicitly initializing it with `undefined` is likely a programmer mistake.

```JS
const x; // SyntaxError: Missing initializer in const declaration
```

#### Variable scope

A variable may belong to one of the following scopes:

- **Global scope**: The default scope for all code running in script mode.
- **Module scope**: The scope for code running in module mode.
- **Function scope**: The scope created with a function.

In addition, variables declared with `let` or `const` can belong to an additional scope:

- **Block Scope**: The scope created with a pair of curly braces(a block).

When you declare a variable outside of any function, it is called a global variable, because it is available to any other code in the current document. When you declare a variable within a function, it is called a local variable, because it is available only within that function.

`let` and `const` declarations can also be scoped to the block statement that they are declared in.

```JS
if (Math.random() > 0.5) {
  const y = 5;
}
console.log(y); // ReferenceError: y is not defined
```

However, variables created with `var` are not block-scoped, but only local to the function (or global scope) that the block resides within.

For example, the following code will log 5, because the scope of x is the global context (or the function context if the code is part of a function). The scope of x is not limited to the immediate if statement block.

```JS
if (true) {
  var x = 5;
}
console.log(x); // x is 5
```

##### Variable Hoisting

`var`-declared variables are hoisted, meaning you can refer to the variable anywhere in its scope, even if its declaration isn't reached yet. You can see var declarations as being "lifted" to the top of its function or global scope. However, if you access a variable before it's declared, the value is always undefined, because only its declaration and default initialization (with undefined) is hoisted, but not its value assignment.

|**Note:**|
|---|
|**Hoisting**: JavaScript Hoisting refers to the process whereby the interpreter appears to move the declaration of functions, variables, classes, or imports to the top of their scope, prior to execution of the code.|

```JS
console.log(x === undefined); // true
var x = 3;

(function () {
  console.log(x); // undefined
  var x = "local value";
})();
```

The above examples will be interpreted the same as:

```JS
var x;
console.log(x === undefined); // true
x = 3;

(function () {
  var x;
  console.log(x); // undefined
  x = "local value";
})();
```

Because of hoisting, all `var` statements in a function should be placed as near to the top of the function as possible. This best practice increases the clarity of the code.

Whether `let` and `const` are hoisted is a matter of definition debate. Referencing the variable in the block before the variable declaration always results in a `ReferenceError`, because the variable is in a "temporal dead zone" from the start of the block until the declaration is processed.

```JS
console.log(x); // ReferenceError
const x = 3;

console.log(y); // ReferenceError
let y = 3;
```

Unlike `var` declarations, which only hoist the declaration but not its value, function declarations are hoisted entirely — you can safely call the function anywhere in its scope. See the hoisting glossary entry for more discussion.

##### Global Variables

Global variables are in fact properties of the global object.

In web pages, the global object is window, so you can read and set global variables using the window.variable syntax. In all environments, the globalThis variable (which itself is a global variable) may be used to read and set global variables. This is to provide a consistent interface among various JavaScript runtimes.

Consequently, you can access global variables declared in one window or frame from another window or frame by specifying the window or frame name. For example, if a variable called phoneNumber is declared in a document, you can refer to this variable from an iframe as `parent.phoneNumber`.

### Constants

You can create a read-only, named constant with the const keyword. The syntax of a constant identifier is the same as any variable identifier: it must start with a letter, underscore, or dollar sign (`$`), and can contain alphabetic, numeric, or underscore characters.

```JS
const PI = 3.14;
```

A constant cannot change value through assignment or be re-declared while the script is running. It must be initialized to a value. The scope rules for constants are the same as those for let block-scope variables.

You cannot declare a constant with the same name as a function or variable in the same scope. For example:

```JS
// THIS WILL CAUSE AN ERROR
function f() {}
const f = 5;

// THIS WILL CAUSE AN ERROR TOO
function f() {
  const g = 5;
  var g;
}
```

However, `const` only prevents re-assignments, but doesn't prevent mutations. The properties of objects assigned to constants are not protected, so the following statement is executed without problems.

```JS
const MY_OBJECT = { key: "value" };
MY_OBJECT.key = "otherValue";
```

Also, the contents of an array are not protected, so the following statement is executed without problems.

```JS
const MY_ARRAY = ["HTML", "CSS"];
MY_ARRAY.push("JAVASCRIPT");
console.log(MY_ARRAY); // ['HTML', 'CSS', 'JAVASCRIPT'];
```

## Data structures and types

### DataTypes

The latest ECMAScript standard defines eight data types:

- Seven data types that are primitives:

  1. Boolean. true and false.
  2. null. A special keyword denoting a null value. (Because JavaScript is case-sensitive, null is not the same as Null, NULL, or any other variant.)
  3. undefined. A top-level property whose value is not defined.
  4. Number. An integer or floating point number. For example: 42 or 3.14159.
  5. BigInt. An integer with arbitrary precision. For example: 9007199254740992n.
  6. String. A sequence of characters that represent a text value. For example: "Howdy".
  7. Symbol. A data type whose instances are unique and immutable.
- and Object

Although these data types are relatively few, they enable you to perform useful operations with your applications. Functions are the other fundamental elements of the language. While functions are technically a kind of object, you can think of objects as named containers for values, and functions as procedures that your script can perform.

### Datatype Conversion

JavaScript is a dynamically typed language. This means you don't have to specify the data type of a variable when you declare it. It also means that data types are automatically converted as-needed during script execution.

So, for example, you could define a variable as follows:

```JS
let answer = 42;
```

And later, you could assign the same variable a string value, for example:

```JS
answer = "Thanks for all the fish!";
```

Because JavaScript is dynamically typed, this assignment does not cause an error message.

#### Numbers and the '+' operator

In expressions involving numeric and string values with the + operator, JavaScript converts numeric values to strings. For example, consider the following statements:

```JS
x = "The answer is " + 42; // "The answer is 42"
y = 42 + " is the answer"; // "42 is the answer"
z = "37" + 7; // "377"
```

With all other operators, JavaScript does not convert numeric values to strings. For example:

```JS
"37" - 7; // 30
"37" * 7; // 259
```

#### Converting strings to numbers

In the case that a value representing a number is in memory as a string, there are methods for conversion.

- parseInt()
- parseFloat()

`parseInt` only returns whole numbers, so its use is diminished for decimals.

>|**Note:**|
>|---------|
>|Additionally, a best practice for `parseInt` is to always include the radix parameter. The radix parameter is used to specify which numerical system is to be used.|

```JS
parseInt("101", 2); // 5
```

There are some alternative methods of retrieving a number from a string is with the `+ (unary plus)` operator or using `Number()`:

- Using `unary plus (+)`

  ```JS
  "1.1" + "1.1"; // '1.11.1'
  (+"1.1") + (+"1.1"); // 2.2
  // Note: the parentheses are added for clarity, not required.
  ```

- Using `Number()`

  ```JS
  "1.1" + "1.1"; // '1.11.1'
  Number("1.1") + Number("1.1"); // 2.2
  // Note: the parentheses are added for clarity, not required.
  ```

## Literals

Literals represent values in JavaScript. These are fixed values—not variables—that you literally provide in your script. This section describes the following types of literals:

- [Array Literals](#array-literals)
- [Boolean Literals](#boolean-literals)
- [Numeric Literals](#numeric-literals)
- [Object Literals](#object-literals)
- [RegExp Literals](#regexp-literals)
- [String Literals](#string-literals)

### Array Literals

An array literal is a list of zero or more expressions, each of which represents an array element, enclosed in square brackets (`[]`). When you create an array using an array literal, it is initialized with the specified values as its elements, and its `length` is set to the number of arguments specified.

The following example creates the `coffees` array with three elements and a `length` of three:

```JS
const coffees = ["French Roast", "Colombian", "Kona"];
```

An array literal creates a new array object every time the literal is evaluated. For example, an array defined with a literal in the global scope is created once when the script loads. However, if the array literal is inside a function, a new array is instantiated every time that function is called.

> **Note:** Array literals create `Array` objects. See [`Array`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array) and [`Indexed collections`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Indexed_collections) for details on Array objects.

#### Extra commas in array literals

If you put two commas in a row in an array literal, the array leaves an empty slot for the unspecified element. The following example creates the `fish` array:

```JS
const fish = ["Lion", , "Angel"];
```

When you log this array, you will see:

```JS
console.log(fish);
// [ 'Lion', <1 empty item>, 'Angel' ]
```

Note that the second item is "empty", which is not exactly the same as the actual undefined value. When using array-traversing methods like [`Array.prototype.map`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/map), empty slots are skipped. However, index-accessing `fish[1]` still returns `undefined`.

If you include a trailing comma at the end of the list of elements, the comma is ignored.

In the following example, the length of the array is three. There is no `myList[3]`and `myList[1]` is empty. All other commas in the list indicate a new element.

```JS
const myList = ["home", , "school"];
```

In the following example, the length of the array is four, and myList[0] and myList[2] are missing.

```JS
const myList = [, "home", , "school"];
```

In the following example, the length of the array is four, and myList[1] and myList[3] are missing. Only the last comma is ignored.

```JS
const myList = ["home", , "school", ,];
```

---
>**Note:** Trailing commas help keep git diffs clean when you have a multi-line array, because appending an item to the end only adds one line, but does not modify the previous line.

```DIFF
const myList = [
  "home",
  "school",
+ "hospital",
];
```

---

Understanding the behavior of extra commas is important to understanding JavaScript as a language.

However, when writing your own code, you should explicitly declare the missing elements as undefined, or at least insert a comment to highlight its absence. Doing this increases your code's clarity and maintainability.

```JS
const myList = ["home", /* empty */, "school", /* empty */, ];
```

### Boolean Literals

The Boolean type has two literal values: `true` and `false`.

>**Note:** Do not confuse the primitive Boolean values true and false with the true and false values of the Boolean object.
>
> The Boolean object is a wrapper around the primitive Boolean data type. See [`Boolean`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Boolean) for more information.

### Numeric Literals

JavaScript numeric literals include integer literals in different bases as well as floating-point literals in base-10.

Note that the language specification requires numeric literals to be unsigned. Nevertheless, code fragments like `-123.4` are fine, being interpreted as a unary `-` operator applied to the numeric literal `123.4`.

#### Integer literals

Integer and `BigInt` literals can be written in decimal (base 10), hexadecimal (base 16), octal (base 8) and binary (base 2).

- A decimal integer literal is a sequence of digits without a leading `0` (zero).
- A leading `0`(zero) on an integer literal, or a leading `0o` (or `0O`) indicates it is in octal. Octal integer literals can include only the digits `0`-`7`.
- A leading `0x` (or `0X`) indicates a hexadecimal integer literal. Hexadecimal integer can include digits (`0` - `9`) and the letter `a` - `f` and `A` - `F`. (The case of a character does not change its value. Therefore: `0xa` = `0xA` = `10` and `0xf` = `0xF` = 15.)
- A leading `0b` (or `0B`) indicates a binary integer literal. Binary integer literals can only include the digits `0` and `1`.
- A trailing `n` suffix on an integer literal indicates a `BigInt` literal. The `BigInt` literal can use any of the above bases. Note that leading-zero octal syntax like `0123n` is not allowed, but `0o123n` is fine.

Some examples of integer literals are:

```Note:
0, 117, 123456789123456789n             (decimal, base 10)
015, 0001, 0o777777777777n              (octal, base 8)
0x1123, 0x00111, 0x123456789ABCDEFn     (hexadecimal, "hex" or base 16)
0b11, 0b0011, 0b11101001010101010101n   (binary, base 2)
```

#### Floating-point literals

A floating-point literal can have the following parts:

- An unsigned decimal integer,
- A decimal point (`.`),
- A fraction (another decimal number),
- An exponent.

The exponent part is an `e` or `E` followed by an integer, which can be signed (preceded by `+` or `-`). A floating-point literal must have at least one digit, and either a decimal point or `e` (or `E`).

More succinctly, the syntax is:

```NOTE
[digits].[digits][(E|e)[(+|-)]digits]
```

**For example:**

```JS
3.1415926
.123456789
3.1E+12
.1e-23
```

### Object Literals

An object literal is a list of zero or more pairs of property names and associated values of an object, enclosed in curly braces (`{}`).

> **Warning**:  Do not use an object literal at the beginning of a statement! This will lead to an error (or not behave as you expect), because the `{` will be interpreted as the beginning of a block.

The following is an example of an object literal. The first element of the `car` object defines a property, `myCar`, and assigns to it a new string, `"Saturn"`; the second element, the `getCar` property, is immediately assigned the result of invoking the function `(carTypes("Honda"))`; the third element, the `special` property, uses an existing variable (`sales`).

```JS
const sales = "Toyota";

function carTypes(name) {
  return name === "Honda" ? name : `Sorry, we don't sell ${name}.`;
}

const car = { myCar: "Saturn", getCar: carTypes("Honda"), special: sales };

console.log(car.myCar); // Saturn
console.log(car.getCar); // Honda
console.log(car.special); // Toyota
```

Additionally, you can use a numeric or string literal for the name of a property or nest an object inside another. The following example uses these options.

```JS
const car = { manyCars: { a: "Saab", b: "Jeep" }, 7: "Mazda" };

console.log(car.manyCars.b); // Jeep
console.log(car[7]); // Mazda
```

Object property names can be any string, including the empty string. If the property name would not be a valid JavaScript identifier or number, it must be enclosed in quotes.

Property names that are not valid identifiers cannot be accessed as a dot (`.`) property.

```JS
const unusualPropertyNames = {
  '': 'An empty string',
  '!': 'Bang!'
}
console.log(unusualPropertyNames.'');   // SyntaxError: Unexpected string
console.log(unusualPropertyNames.!);    // SyntaxError: Unexpected token !
```

Instead, they must be accessed with the bracket notation (`[]`).

```JS
console.log(unusualPropertyNames[""]); // An empty string
console.log(unusualPropertyNames["!"]); // Bang!
```

#### Enhanced Object literals

Object literals support a range of shorthand syntaxes that include setting the prototype at construction, shorthand for `foo: foo` assignments, defining methods, making `super` calls, and computing property names with expressions.

Together, these also bring object literals and class declarations closer together, and allow object-based design to benefit from some of the same conveniences.

```JS
const obj = {
  // __proto__
  __proto__: theProtoObj,
  // Shorthand for 'handler: handler'
  handler,
  // Methods
  toString() {
    // Super calls
    return "d " + super.toString();
  },
  // Computed (dynamic) property names
  ["prop_" + (() => 42)()]: 42,
};
```

### RegExp Literals

A regex literal (which is defined in detail later) is a pattern enclosed between slashes. The following is an example of a regex literal.

```JS
const re = /ab+c/;
```


### String Literals

A string literal is zero or more characters enclosed in double (`"`) or single (`'`) quotation marks. A string must be delimited by quotation marks of the same type (that is, either both single quotation marks, or both double quotation marks).

The following are examples of string literals:

```JS
'foo'
"bar"
'1234'
'one line \n another line'
"Joyo's cat"
```

You should use string literals unless you specifically need to use a `String` object. See [`String`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String) for details on String objects.

You can call any of the String object's methods on a string literal value. JavaScript automatically converts the string literal to a temporary String object, calls the method, then discards the temporary String object. You can also use the length property with a string literal:

```JS
// Will print the number of symbols in the string including whitespace.
console.log("Joyo's cat".length); // In this case, 10.
```

Template literals are also available. Template literals are enclosed by the back-tick (`` ` ``) (grave accent) character instead of double or single quotes.

Template literals provide syntactic sugar for constructing strings. (This is similar to string interpolation features in Perl, Python, and more.)

```JS
// Basic literal string creation
`In JavaScript '\n' is a line-feed.`

// Multiline strings
`In JavaScript, template strings can run
 over multiple lines, but double and single
 quoted strings cannot.`

// String interpolation
const name = 'Lev', time = 'today';
`Hello ${name}, how are you ${time}?`

```

Tagged templates are a compact syntax for specifying a template literal along with a call to a "tag" function for parsing it. A tagged template is just a more succinct and semantic way to invoke a function that processes a string and a set of relevant values. The name of the template tag function precedes the template literal — as in the following example, where the template tag function is named `print`. The `print` function will interpolate the arguments and serialize any objects or arrays that may come up, avoiding the pesky `[object Object]`.

```JS
const formatArg = (arg) => {
  if (Array.isArray(arg)) {
    // Print a bulleted list
    return arg.map((part) => `- ${part}`).join("\n");
  }
  if (arg.toString === Object.prototype.toString) {
    // This object will be serialized to "[object Object]".
    // Let's print something nicer.
    return JSON.stringify(arg);
  }
  return arg;
};

const print = (segments, ...args) => {
  // For any well-formed template literal, there will always be N args and
  // (N+1) string segments.
  let message = segments[0];
  segments.slice(1).forEach((segment, index) => {
    message += formatArg(args[index]) + segment;
  });
  console.log(message);
};

const todos = [
  "Learn JavaScript",
  "Learn Web APIs",
  "Set up my website",
  "Profit!",
];

const progress = { javascript: 20, html: 50, css: 10 };

print`I need to do:
${todos}
My current progress is: ${progress}
`;

// I need to do:
// - Learn JavaScript
// - Learn Web APIs
// - Set up my website
// - Profit!
// My current progress is: {"javascript":20,"html":50,"css":10}
```

Since tagged template literals are just sugar of function calls, you can re-write the above as an equivalent function call:

```JS
print(["I need to do:\n", "\nMy current progress is: ", "\n"], todos, progress);
```

This may be reminiscent of the `console.log`-style interpolation:

```JS
console.log("I need to do:\n%o\nMy current progress is: %o\n", todos, progress);
```

You can see how the tagged template reads more naturally than a traditional "formatter" function, where the variables and the template itself have to be declared separately.

#### Using a special characters in strings

In addition to ordinary characters, you can also include special characters in strings, as shown in the following example.

```JS
"one line \n another line";
```

The following table lists the special characters that you can use in JavaScript strings.

| Character	| Meaning |
|-----------|---------|
|\0	|Null Byte|
|\b	|Backspace|
|\f	|Form Feed|
|\n	|New Line|
|\r	|Carriage Return|
|\t	|Tab|
|\v	|Vertical tab|
|\'	|Apostrophe or single quote|
|\"	|Double quote|
|\\	|Backslash character|
|\XXX	|The character with the Latin-1 encoding specified by up to three octal digits XXX between 0 and 377. For example, \251 is the octal sequence for the copyright symbol.|
|\xXX |	The character with the Latin-1 encoding specified by the two hexadecimal digits XX between 00 and FF. For example, \xA9 is the hexadecimal sequence for the copyright symbol.|
|\uXXXX	|The Unicode character specified by the four hexadecimal digits XXXX. For example, \u00A9 is the Unicode sequence for the copyright symbol. See Unicode escape sequences.|
|\u{XXXXX}|	Unicode code point escapes. For example, \u{2F804} is the same as the Unicode escapes \uD87E\uDC04.|

#### Escaping characters

For characters not listed in the table, a preceding backslash is ignored, but this usage is deprecated and should be avoided.

You can insert a quotation mark inside a string by preceding it with a backslash. This is known as escaping the quotation mark. For example:

```JS
const quote = "He read \"The Cremation of Sam McGee\" by R.W. Service.";
console.log(quote);
```

The result of this would be:

```
He read "The Cremation of Sam McGee" by R.W. Service.
```

To include a literal backslash inside a string, you must escape the backslash character. For example, to assign the file path c:\temp to a string, use the following:

```JS
const home = "c:\\temp";
```

You can also escape line breaks by preceding them with backslash. The backslash and line break are both removed from the value of the string.

```JS
const str =
"this string \
is broken \
across multiple \
lines.";
console.log(str); // this string is broken across multiple lines.
```
