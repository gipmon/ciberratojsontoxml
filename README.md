--------------
Menu interface
--------------


----------------------
Command Line Arguments
----------------------


---------------
Web Service API
---------------
URL: http://lfa.rafaelferreira.pt/

Password: lfaworkteam

The web page will be public on Thursday

--------------
Class Hierachy
--------------

      +---------+      +--------------+   +---------------+  +-----+
      |Challenge+------+ExtraParamList+---+ParametersClass+--+Param|
      +----+----+      +--------------+   +-------+-------+  +--+--+
           |                                      |             |   
      +----+----+  +----------+           +-------+-------+  +--+--+
      +  maze   +--+dimensions|           | class_name    |  |name |
      +----+----+  +----------+           | Vector Param  |  |value|
           |                              +---------------+  +-----+
           |                         +------------+                         
           |  +----+----+  +------+  | position   |                         
           |--| beacons +--+beacon+--+ height     |                         
           |  +---------+  +------+  +------------+                         
           |                               +------+-+                       
           |  +-----------+  +----------+  |position|                       
           |--+targetareas+--+targetarea+--+radius  |                       
           |  +-----------+  +----------+  +--------+                       
           |                    +----------+ +-----------+   +-------+        
           |    +-----+ +----+  |height    +-+corner list+---+ Point |        
           +----+walls+-+wall+--+thickness | +-----------+   +-------+        
           |    +-----+ +----+  +----------+                                  
           |    +-----+  +---------+  +----+     +--------------------+       
           +----+grid +--+posesList+--+Pose|   +-+ name, first point, |       
           |    +-----+  +---------+  +----+   | | second point,      |       
           |    +-----+--+    +----+--+        | | thickness,         |       
           +----+ models +----+ model +--------+ | height             |       
           |    +--------+    +--+----+          +--------------------+       
           |    +--------+---+   +----+-----+   +---------------------+---+   
           +----+SuperModels +---+SuperModel+---+ name, names_models_list |   
                +------------+   +----------+   +-------------------------+   

--------
Features
--------

1. Validations

⋅⋅ Default Values:

⋅⋅ Scenario description:

⋅⋅ Last parameters:

2. Errors Handling
⋅⋅ 

3. XML
⋅⋅

4. URDF
⋅⋅

5. Models and Super Models
⋅⋅

5. API
⋅⋅