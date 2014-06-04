$( document ).ready(function() {
    $("#make").click(function(){ 
		var param = $('#param').val();
		var challange = $('#challange').val();
		$('#output').text('Please wait a moment!');
		$.post("compiling.php",{param: param, challange: challange}, function(data){
			var response = jQuery.parseJSON(data);
			if(typeof response =='object'){
				$('#grid').text(response.grid_output);
				$('#lab').text(response.lab_output);
				$('#param').text(response.param_output);
				$('#urdf').text(response.urdf_output);
				console.log(response.param_output);
				$('#output').text("OUTPUT done!");
			}else{
				$('#output').text(data);
			}
		});
    }); 
});