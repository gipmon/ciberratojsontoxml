Menu interface
==============
* Para utilizar o programa através de um menu, basta invocar o seguinte comando:
./main.output

Command Line Arguments
======================


Web Service API
===============
URL: http://lfa.rafaelferreira.pt/

Password: lfaworkteam

A página vai ser tornada pública na Quinta-feira.

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
           |    +------------+   +----------+   +-------------------------+   
           +----+SuperModels +---+SuperModel+---+ name, names_models_list |   
                +------------+   +----------+   +-------------------------+   

Features
========

1. Validations (Challenge)
--------------

Default Values:

* Challenge Name == NULL (Excepção)

* Challenge Type == NULL (Excepção)

* Cycle Time <= 0 || Cycle Time não é valor inteiro (Excepção)

* Duration <= 0 || Duration não é valor inteiro (Excepção)

Scenario description:

* Scenario description name == NULL (Excepção)

* Dimensões, x <= 0 || y <= 0 (Excepção)

* Número de Faróis < 0 (Excepção)

* Posição Faróis > Dimensões && Posição Faróis < 0 (Warning)

* Altura Farol <= 0 (Excepção)

* Número de Áreas Alvo > 0 (Excepção)

* Posição Áreas Alvo > Dimensões && Posição Áreas Alvo < 0 (Warning)

* Raio Área Alvo <= 0 (Excepção)

* Posição Paredes > Dimensões && Posição Paredes < 0 (Warning)

* Altura Parede <= 0 (Excepção)

* Thickness Parede < 0 (Excepção)

* Número de Grelhas de Partida > 0 (Excepção)

* Altura model <= 0 (Excepção)

* Posição Models > Dimensões && Posição Models < 0 (Warning)

* Thickness Model < 0 (Excepção)

Last parameters:
* Classe não existir na tabela de Símbolos (Excepção)
* Se o parâmetro não existir (Excepção)
* Valor não corresponde ao value type (Excepção)

2. Errors Handling
------------------
**Tratamento de Excepções**

A função Errors Handling, serve para fazer o tratamento de excepções, tanto Semânticos, como de Parsing.

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