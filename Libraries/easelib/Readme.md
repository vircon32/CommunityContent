![](https://files.catbox.moe/ibgyl8.png)

---

### What is Easelib?
Easelib is a single file header designed for Vircon32, includes only one function known as **ease** which is the only one responsible for calculating easing effects.


### What can it do?
At the moment (Version 1.0) Easelib can:
* Produce ease-in effect
* Produce ease-out effect
* Produce a combined effect (ease-in + ease-out)

And these effects:
* NONE
* LINEAR
* SINE
* CUBIC
* QUINT	
* CIRC
* BACK

---

# USAGE
Easelib is simple yet also limited on it's own, but a bit of math can do magic! (wanna see examples? check the demo!!!)

### 1. DEFINE

include the library on your main C file:  
_path might change depending on your project._
~~~
#include "easings.h" 

void main(void){

}
~~~

### 2. USE EASE FUNCTION

Finally the main protagonist here, the ease function:
~~~
float ease(float time, int ease_in, int ease_out)
~~~
The ease function uses 3 arguments: a timer (from 0.0 to 1.0), ease in and ease out effect selection.  
if used correctly it should return a floating value from 0 to 1 which is the result of calculating easings based on the timer.

However, since the values it returns are between 0 and 1, is recommended to multiply it in order to increase it's amplitude:

~~~
(offset + ease(timer, EASE, EASE) * amplitude)
~~~

---

_made with Ɛ> by @Palta for everyone!
 under the_ [MIT License](https://opensource.org/license/mit)
