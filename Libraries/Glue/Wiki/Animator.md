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

### glue_move_edit(int key, int type)
modifies keyframe state
- _**Key**_ = Keyframe
- _**Type**_ = modification type
     - **go_start** = goes to the beginning
     - **go_end** = ends the animation
     - **go_pause** = pauses the animation
     - **go_continue** = continues the previously paused animation

#### syntax:
```
initial = glue_move( key, initial, final, velocity, type );
```
- _**Key**_ =	keyframe
- _**Initial**_ =	initial value (or variable)
- _**final**_ =	final value
- _**velocity**_ = velocity
- _**type**_ = movement type
