Menu interface
==============

Command Line Arguments
======================


Web Service API
===============
URL: http://lfa.rafaelferreira.pt/

Password: lfaworkteam

The web page will be public on Thursday

Class Hierachy
==============

      +---------+      +--------------+   +---------------+  +-----+
      |Challenge+------+ExtraParamList+---+ParametersClass+--+Param|
      +----+----+      +--------------+   +-------+-------+  +--+--+
           |                                      |             |   
      +----+----+  +----------+           +-------+-------+  +--+--+
      +  maze   +--+dimensions|           | class_name    |  |name |
      +----+----+  +----------+           | Vector Param  |  |value|
           |                              +---------------+  +-----+
           |                           +------------+                         
           |    +---------+  +------+  | position   |                         
           |----| beacons +--+beacon+--+ height     |                         
           |    +---------+  +------+  +------------+                         
           |                                 +--------+                       
           |    +-----------+  +----------+  |position|                       
           |----+targetareas+--+targetarea+--+radius  |                       
           |    +-----------+  +----------+  +--------+                       
           |                    +----------+ +-----------+   +-------+        
           |    +-----+ +----+  |height    +-+corner list+---+ Point |        
           +----+walls+-+wall+--+thickness | +-----------+   +-------+        
           |    +-----+ +----+  +----------+                                  
           |    +-----+  +---------+  +----+     +--------------------+       
           +----+grid +--+posesList+--+Pose|   +-+ name, first point, |       
           |    +-----+  +---------+  +----+   | | second point,      |       
           |    +--------+    +-------+        | | thickness,         |       
           +----+ models +----+ model +--------+ | height             |       
           |    +--------+    +-------+          +--------------------+       
           |    +------------+   +----------+   +---------------------+---+   
           +----+SuperModels +---+SuperModel+---+ name, names_models_list |   
                +------------+   +----------+   +-------------------------+   

Features
========

1. Validations
--------------
Default Values:

Scenario description:

Last parameters:

2. Errors Handling
------------------

3. XML
------

4. URDF
-------

5. Models and Super Models
--------------------------
** Models**

Os models permite instanciar várias paredes nas walls tendo ambas uma forma pré-definida. Ao instanciar é possível fazer uma translação em x e em y, assim como uma rotação em torno do seu eixo em radianos. 

*Um model é definido* por um nome que o identifica, uma height que tem de ser >0, um thickness >=0 e dois pontos: first and second.

{ "name" : "nome_do_modelo", "height" : 1, "thickness" : 0.2, "first point" : [9,0], "second point" : [7, 2] },

![models.jpg](https://bitbucket.org/repo/bgd4ap/images/109638247-models.jpg)

**Super Models**

Um super model é uma lista de models que podem ser instanciados ao mesmo tempo nas walls. Sendo este caracterizado por um nome que o identifica e uma lista de nomes que identificam os models associados. Ao instanciar um super model nas walls é possível fazer as mesmas operações de translação e rotação que são possíveis num model.

5. API
------