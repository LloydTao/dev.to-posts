# The Case for Comma-Leading Lists

## Introduction

Comma-leading lists are an objectively better presentation style.

They make **logical sense**; the next value on the list is dependant on the comma, and so, they should be kept together.

The style may look alien at first, but give it a test drive and you'll be surprised at how quickly it starts to look normal.

For now, let's have a look at the benefits.

---

## Justification

### 1. No Merge Conflicts

When adding a new value to a list with trailing commas, you're making 2 additions and 1 deletion.

![Comma-Trailing List Diff](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/general/comma-leading-lists/trailing-diff.png)

This will give you a **merge conflict** just because someone else adds a value on a different branch.

By using the comma-leading style, you make 1 addition and 0 deletions.

![Comma-Leading List Diff](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/general/comma-leading-lists/leading-diff.png)

These commits play ball with each other, without needing any conflict resolution.

"*Ah, but I've used a dangling comma*," you say? Allow me to continue.

### 2. Dangling Commas Bad

It's true that using a trailing comma after the final value will prevent conflicts, but it's dumb for two reasons.

**1. Language Inconsistency**

**SQL** doesn't support them. 

![Comma-Leading JSON](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/general/comma-leading-lists/leading-sql.png)

**The JSON standard** and **Pre-ES5 JavaScript** doesn't support them.

![Comma-Leading JSON](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/general/comma-leading-lists/leading-json.png)

It's better to stick to a style that works across more languages, especially for a multi-lingual codebase.

**2. Redundant Logic**

There's not a second element. It's unnecessary context, so why justify it?

And, if an interpreter *ever* decides to stick a `None` in there, good luck.

### 3. Better Presentation

**Separating Context**

With the comma-leading style, the logic stays on the left, and the data stays on the right.

This makes it quicker and easier to scan when looking through code.

![Better Presentation](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/general/comma-leading-lists/presentation.png)

It will also allow you to quickly identify logic errors, such as missing commas.

![Leaking Globals](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/general/comma-leading-lists/leaked-globals.png)

**Saving Whitespace**

When you indent after the opening bracket, you're adding extra columns of whitespace on the left-hand side.

Placing the commas on the left keeps the code neat and narrow. Neat!

---

## Summary

Comma-leading lists are easier for source control, more compatible across languages, and much faster to read since they keep data separate from the list's logic.

Do the world a favour and switch to a better standard of data structure.

```haskell
animals = [ "ant"
          , "bat"
          , "cat"
          , "dog"
          ]
```

What's not to love? 😉

---

Hey, guys! Thank you for reading. I hope that you enjoyed this.

Keep up to date with me:

- DEV: https://dev.to/tao/
- Twitter: https://twitter.com/LloydTao
- GitHub: https://github.com/LloydTao
- LinkedIn: https://www.linkedin.com/in/LloydTao/

Catch you around!
