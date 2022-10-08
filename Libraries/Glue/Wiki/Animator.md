# Glue Animator

 make nice and smooth movements

## import
1. Define glue_AnimLimit 
2. import glue_animator

**example:**
```
#define glue_AnimLimit 3

#import "glue_animator"
```

## Usage
### glue_move_start()
use it only once and outside of a loop
clears all the values

### glue_move_edit( int key, int type )
modifies keyframe state

- _**Key**_ = Keyframe
- _**Type**_ = modification type
     - **go_start (0)** = goes to the beginning
     - **go_end (1)** = ends the animation
     - **go_pause (2)** = pauses the animation
     - **go_continue (3)** = continues the previously paused animation
     - **delete_key (4)** =deletes the keyframe



### glue_move( int key, float init, float finish, float velocity, int type )

```
initial = glue_move( key, initial, final, velocity, type );
```
- _**Key**_ =	keyframe
- _**Initial**_ =	initial value (or variable)
- _**final**_ =	final value
- _**velocity**_ = velocity
- _**type**_ = movement type
