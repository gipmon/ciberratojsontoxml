# **Relatório** (README.md) #

Menu interface
==============
Para utilizar o programa através de um menu, basta invocar o seguinte comando:
./main.output

**MENU:**

1 - Read parameters list file (.json)

2 - Read challenge parameters file (.json)

3 - Print to XML

4 - Print URDF

5 - Add Model to Walls

6 - Clear not perpendicular walls

7 - Create Super Model

8 - Add model to Super Model

9 - Add Super Model to walls

10 - Stats

0 - End Program

Command Line Arguments
======================

**OPTIONS:**

-p : print tables

-o : output to xml

-s : permite escolher o local para o output dos ficheiros (API)

./main.output : Menu with more options

It should be passed the two files .json or nothing!

**Example:**

./main.output -o ../exemplos/json/param-list.json ../exemplos/json/example.json

./main.output -p ../exemplos/json/param-list.json ../exemplos/json/example.json

./main.output -p -o ../exemplos/json/param-list.json ../exemplos/json/example.json

Web Service API
===============
URL: http://lfa.rafaelferreira.pt/

É possível fazer download do ficheiro.

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

1. Validations
--------------

**(Challenge)**

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

No final, se os parâmetros que têm default value não estiverem definidos são inseridos com o default value correspondente.

**(Parameters list)**

Sempre que um parâmetro for adicionado na primeira tabela de símbolos, o "default value" é verificado para saber se está em concordância com o "value type". Assim como se na class que este está a ser inserido já está definido.

2. Errors Handling
------------------
**Tratamento de Excepções**

A função Errors Handling, serve para fazer o tratamento de excepções, tanto Semânticos, como de Parsing.

Esta função está disponível em: main.cpp

3. XML
------
**Grid**

O *Grid.xml* consiste na grelha de partida que indica as posições e orientações dos robôs no início de uma simulação. É representada por um array de triplos, cada um contendo uma posição e uma direção.


```
#!json

{"grid" : [ [x, y, dir] ]}
```


Os valores de *x, y e dir* previamente processados e guardados numa estrutura de dados, são impressos pela função *gridOutputXML*.


```
#!xml

<Grid> <Position X="x" Y="y" Dir="dir"/> </Grid>
```


**Lab**

O *Lab.xml* consiste na descrição do cenário de simulação. Esta descrição contém elementos tais como:

* Name: Nome do cenário.
* Dimensions: consiste num par comprimento/largura que define o tamanho do cenário de simulação.
* Beacons: posição e altura do farol, para onde o robot se deve dirigir.
* Target Areas: área alvo, centrada no mesmo ponto do farol com um determinado raio.
* Walls: definição das posições das paredes. Consiste num conjunto de parâmetros para definir a altura da parede(height), grossura da parede(thickness), e um conjunto de pontos(corner list), em que cada par de pontos consecutivos define uma parede.


```
#!json

"scenario description" : {
   "name" : "TOS challenge",
   "dimensions" : [28, 14],
   "beacons" : [ { "position" : [14, 7], "height" : 2 } ],
   "target areas" : [ { "position" : [14, 7], "radius" : 1} ],
   "walls" : [ { "height" : 1, "thickness" : 0.3, "corner list" : [ [0, 1], [1, 1], [1, 0] ] } ] }

```

Todos estes valores, depois de guardados, são impressos na função *gridOutputXML* da seguinte maneira:


```
#!xml

<Lab Name="TOS challenge" Width="28" Height="14">
   <Beacon X="14" Y="7" Height="2"/>
   <Target X="14" Y="7" Radius="1"/>
   <Wall Height="1">
      <Corner X="0" Y="1"/>
      <Corner X="1" Y="1"/>
      <Corner X="1" Y="0"/>
   </Wall>
</Lab>
```


**Param**

O *Param.xml* contém os parâmetros de simulação utilizados. São representados pelo nome do parâmetro seguido do seu valor.


```
#!json

{ "parâmetro" : "valor" }
```


Os nomes e os valores dos parâmetros, depois de validados e guardados, são impressos pela função *paramOutputXML*. Só são impressos os parâmetros que constem no ficheiro param-list.json e os parametros que tenham default value, são automaticamente inseridos no xml com esse default value.


```
#!xml

<Parameters parametro="valor" />
```


4. URDF
-------
Ficheiro URDF.xml gerado com toda a informação necessária para a completa construção e simulação 3D do cenário especificada no ficheiro de entrada example.json. Analisando aspectos como height, thickness e corner list, e através de alguma trigonometria adicional é possível modelar e dispor cada parede no cenário. 
Para cada lista de pontos definida no ficheiro de entrada, por exemplo:





```
#!json

{ "height" : h, "thickness" : t, "corner list" : [ [x1,y1], [x2, y2], [x3, x4] ] }
```





é realizado um *for* percorrendo os pontos, em que o ponto atual e o seguinte formam uma parede. Para isso efetuam-se alguns cálculos:




* Cálculo do ponto médio entre os dois pontos: ((*x1 + x2*)/2 , (*y1 + y2*)/2) = (*x12, y12*) = *ponto médio*
* Cálculo do ângulo de rotação em torno do eixo z, formado pelos dois pontos, usando a função atan2(y2-y1,x2-x1) = *angulo*
* Cálculo do comprimento da parede: sqrt((*x1 - x2*)^2 + (*y1 - y2*)^2) = *comprimento*.




Depois destes cálculos a parede é impressa em URDF da seguinte maneira:





```
#!xml

<link name="nome da parede">
   <visual>
   <origin xyz="xMedio yMedio 0" rpy="0 0 angulo"/>
   <geometry>
      <box size="comprimento thickness height"/>
   </geometry>
   <material name="Color"/>
   </visual>
</link>
```





No caso de duas paredes formarem um ângulo recto entre si(produto interno entre as duas paredes = 0), é adicionado um complemento para para a parede ficar bem definida.

![ScreenShot 2014-06-8, às 23.00.22.png](https://bitbucket.org/repo/bgd4ap/images/4088023536-ScreenShot%202014-06-8%2C%20%C3%A0s%2023.00.22.png)

Este complemento é gerado da seguinte maneira:

* Ponto médio: Segundo ponto da primeira parede(equivalente ao primeiro ponto da segunda parede).
* Cálculo do ângulo de rotação em torno do eixo z: igual ao da primeira parede(ou da segunda).
* Dimensões da parede: quadrado de lado thickness.

```
#!xml

<link name="nome do complemento">
   <visual>
   <origin xyz="xMedio yMedio 0" rpy="0 0 angulo"/>
   <geometry>
      <box size="thickness thickness height"/>
   </geometry>
   <material name="Color"/>
   </visual>
</link>
```

Será gerado, ainda, um outro URDF.xml em que as paredes(com ângulos rectos) não terão o complemento, porém todas as paredes poderão rodar sobre o seu centro. Isto é conseguido usando joint's da seguinte maneira:


Definição do tamanho e orientação da parede:

```
#!xml

<link name="parede1">
   <visual>
   <origin xyz="0 0 0" rpy="0 0 angulo"/>
   <geometry>
      <box size="comprimento thickness height"/>
   </geometry>
   <material name="Cyan1"/>
   </visual>
</link>
```


Definição do eixo de rotação:

```
#!xml

<joint name="joint1" type="continuous">
   <parent link="parede1"/>
   <child link="parede1"/>
   <origin xyz="xMedio yMedio 0" rpy="0 0 0"/>
   <axis xyz="0 0 1"/>
</joint>
```


5. Models and Super Models
--------------------------
** Models**

Os models permite instanciar várias paredes nas walls tendo ambas uma forma pré-definida. Ao instanciar é possível fazer uma translação em x e em y, assim como uma rotação em torno do seu eixo em radianos.

*Um model é definido* por um nome que o identifica, uma height que tem de ser >0, um thickness >=0 e dois pontos: first and second.


```
#!json

{ "name" : "nome_do_modelo", "height" : 1, "thickness" : 0.2, "first point" : [9,0], "second point" : [7, 2] }
```


![models.jpg](https://bitbucket.org/repo/bgd4ap/images/109638247-models.jpg)

**Super Models**

Um super model é uma lista de models que podem ser instanciados ao mesmo tempo nas walls. Sendo este caracterizado por um nome que o identifica e uma lista de nomes que identificam os models associados. Ao instanciar um super model nas walls é possível fazer as mesmas operações de translação e rotação que são possíveis num model.

5. API
------

A API está disponível aqui: http://lfa.rafaelferreira.pt/api.php assim como os parâmetros POST para o pedido e os vários tipos de resposta.