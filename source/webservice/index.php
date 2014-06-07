<?php
  if($_POST['password']=="lfaworkteam"):
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>LFA :: MicroRato :: JSON to XML</title>

    <link href="//netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css" rel="stylesheet">
    <link href="css/bootstrap-theme.min.css" rel="stylesheet">
    <link href="css/theme.css" rel="stylesheet">

  </head>

  <body role="document">

    <div class="navbar navbar-inverse navbar-fixed-top" role="navigation">
      <div class="container">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand" href="#">[LFA] JSON to XML</a>
        </div>
        <div class="navbar-collapse collapse">
          <ul class="nav navbar-nav">
            <li class="active"><a href="index.php">Json to XML</a></li>
            <li><a href="api.php" style="color: #B00000"><strong>API</strong></a></li>
            <li><a href="http://mymodelrobot.appspot.com/" target="_blank">URDF viewer</a></li>
            <li class="dropdown">
              <a href="#" class="dropdown-toggle" data-toggle="dropdown">Membros <b class="caret"></b></a>
              <ul class="dropdown-menu">
                <li><a href="http://www.rafaelferreira.pt/">Rafael Ferreira</a></li>
                <li><a href="#">Bernardo Ferreira</a></li>
                <li><a href="https://www.facebook.com/rlopescunha">Rodrigo Cunha</a></li>
                <li><a href="https://www.facebook.com/profile.php?id=100000144346090">Rafael Almeida</a></li>
                <li><a href="https://www.facebook.com/quintanilha.joao.9">João Quintanilha</a></li>
              </ul>
            </li>
          </ul>
        </div>
      </div>
    </div>
    <?php
    $parameters_file = "../../exemplos/json/param-list.json";
    $parameters_file_handling = fopen($parameters_file, 'r') or die("UPS! Something went wrong!");
    $parameters = fread($parameters_file_handling, filesize($parameters_file));
    fclose($parameters_file_handling);

    $challenge_file = "../../exemplos/json/example.json";
    $challenge_file_handling = fopen($challenge_file, 'r') or die("UPS! Something went wrong!");
    $challenge = fread($challenge_file_handling, filesize($challenge_file));
    fclose($challenge_file_handling);
    ?>
    <div class="container theme-showcase" role="main">
      <h3>JSON input (param list and challenge list)</h3>
      <div class="row">
        <div class="col-md-6"><h4>param.json:</h4><br/><textarea style="width: 100%" id="param" rows="15"><?=$parameters?></textarea></div>
        <div class="col-md-6"><h4>challenge.json:</h4><br/><textarea style="width: 100%" id="challenge" rows="15"><?=$challenge?></textarea></div>
      </div>
      <p style="text-align: center">
        <button type="button" id="make" class="btn btn-primary btn-lg">Make XML</button>
      </p>
      <hr/>
      <h4>OUTPUT</h4>
      <pre id="output"></pre>
      <div id="output_div" style="display:none">
        <hr/>
        <h3>XML output</h3>
        <div class="row">
          <div class="col-md-6"><h4>Grid.xml:</h4><br/><textarea style="width: 100%" id="grid" rows="30" readonly></textarea></div>
          <div class="col-md-6"><h4>Lab.xml:</h4><br/><textarea style="width: 100%" id="lab" rows="30" readonly></textarea></div>
        </div>
        <div class="row">
          <div class="col-md-6"><h4>Param.xml:</h4><br/><textarea style="width: 100%" id="param_output"  rows="30" readonly></textarea></div>
          <div class="col-md-6"><h4>URDFFixed.xml:</h4><br/><textarea style="width: 100%" id="urdf_xml_output_fixed" rows="30" readonly></textarea></div>
        </div>
        <div class="row">
          <div class="col-md-6"><h4>URDFRotate.xml:</h4><br/><textarea style="width: 100%" id="urdf_xml_output_rotate"  rows="30" readonly></textarea></div>
        </div>
      </div>
    </div>

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.0/jquery.min.js"></script>
    <script src="//netdna.bootstrapcdn.com/bootstrap/3.1.1/js/bootstrap.min.js"></script>
    <script src="jquery/jq.js"></script>
  </body>
</html>
<?php else: ?>
  <form method="post" action="">
    <input type="password" name="password">
    <input type="submit">
  </form>
<?php endif; ?>