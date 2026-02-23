![](https://i.postimg.cc/6pbwtzH9/pgoodies.png)
---

A collection of useful functions bundled into one single library.

---
# FUNCTIONS

## wrap
~~~
wrap(int index, int range)
~~~
Wraps around an `index` number inside a `range`

```
range = 6              
                        
  0 1 2 3 4 5 6 7 8 9 10 
  ⋀           │          
  └───────────┘          
```



</br>

## lerp

~~~
lerp(float a, float b, float f)
~~~

Calculates linear interpolation between `a` and `b` being `f` a percentage (between 0 and 1)

```
f = 0.25               
                        
  a     ▿              b 
  ●-----┴--------------● 

```





</br>

## clamp

~~~
clamp(float value, float min, float max)
~~~

Forces `value` to be between `min` and `max`

```
min:4 max:9                             
                                        
normal   0 1 2 3 4 5 6 7 8 9 10 11 12 13
                                        
clamp    4 4 4 4 4 5 6 7 8 9 9  9  9  9 
                 │─────────│            
```





</br>

## rand_between

~~~
rand_between(int min, int max)
~~~

Returns a random value between `min` and `max`



</br>

## point_in_circle

~~~
point_in_circle(int px, int py, int cx, int cy, int radius)
~~~
checks if a point is inside a circle.

defined as:
- `px`      Point X
- `py`      Point Y
- `cx`      Circle center X
- `cy`      Circle center Y
- `radius`  Circle radius

```
                      
          #######     
        ##       ##   
       #           #  
false  #     #     # ∙
       #           #  
        ##       ##   
          #######     
                      
          #######     
        ##       ##   
       #           #  
 true  #     #  ∙  #  
       #           #  
        ##       ##   
          #######     
```




</br>

## circle_in_circle

~~~
circle_in_circle(int circle_1_x, int circle_1_y, int circle_1_radius, int circle_2_x, int circle_2_y, int circle_2_radius)
~~~

checks if a two circles are colliding

```
          #######        #######   
        ##       ##    ##       ## 
       #           #  #           #
false  #     #     #  #     #     #
       #           #  #           #
        ##       ##    ##       ## 
          #######        #######   
                                   
          #######  #######         
        ##       ##       ##       
       #        #  #        #      
 true  #     #  #  #  #     #      
       #        #  #        #      
        ##       ##       ##       
          #######  #######         
```





</br>

## point_in_box

~~~
point_in_box(float px, float py, float bx, float by, float w, float h)
~~~

checks if two rectangles are touching

defined as:
- `px`      Point X
- `py`      Point Y
- `bx`      box X
- `by`      box Y
- `w`       box width
- `h`       box height


```                
       ┌─────┐  
false  │     │ ∙
       │     │  
       └─────┘  
                
       ┌─────┐  
       │   ∙ │  
 true  │     │  
       └─────┘  
```





</br>

## box_in_box

~~~
box_in_box (int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
~~~

checks if two rectangles are touching

```                
               ┌─────┐ 
       ┌─────┐ │     │ 
false  │     │ │     │ 
       │     │ └─────┘ 
       └─────┘         
                       
          ┌─────┐      
       ┌──┼──┐  │      
 true  │  │  │  │      
       │  └──┼──┘      
       └─────┘              
```





</br>

## print_int

~~~
print_int(int x,int y, int num, int base)
~~~

prints `num` at `x` and `y` position with the desired `base` (2 for binary, 10 for decimal, 15 for hexadecimal)





</br>

## print_float

~~~
print_float(int x,int y, float num)
~~~

prints `num` at `x` and `y`, this time showing all the decimals






</br>

## BITWISE FUNCTIONS
functions to modify raw bits in numbers:
- `setbit(int *n, int k)`: set `K`th bit to 1.
- `clearbit(int *n, int k)`: set `K`th bit to 0.
- `togglebit(int *n, int k)`: set `K`th bit to 1 if it was 0 and vice-versa.
- `modifybit(int *n, int k, int p)`: set `K`th bit to `p` value
- `findbit(int n, int k)`: return `K`th bit value.



</br>

## DEFINITIONS

### deg
precalculated radian to degree convertion.

_number_in_radians*deg = number_in_degrees_

    deg = 0.0174532925199432957692369


### rad
precalculated degree to radian convertion.

_number_in_degrees*deg = number_in_radians_ 

    rad = 57.2957795130823208767982



### tau
precalculated **𝜏** constant.

    tau = 1.57079632679489661923132



### euler
precalculated **e** constant.

    rad = 57.2957795130823208767982



### golden
precalculated **golden radio** constant.

    golden = 1.61803398874989484820459



### pythagoras
precalculated **pythagoras** constant √(2).

    pythagoras = 1.41421356237309504880169



<br/><br/>


---

_made with Ɛ> by @Palta for everyone!
 under the_ [MIT License](https://opensource.org/license/mit)
