$( document ).ready(function() {
    $("#make").click(function(){ 
		var param = $('#param').val();
		var challange = $('#challange').val();
		$('#output').text('Please wait a moment!');
		$.post("compiling.php",{param: param, challange: challange}, function(data){
			var response = jQuery.parseJSON(data);
			if(typeof response =='object'){
				if(response.response_type=="error"){
					$('#output').text(response.val);
				}else if(response.response_type=="ok"){
					$('#grid').text(response.val.grid_output);
					$('#lab').text(response.val.lab_output);
					$('#param_output').text(response.val.param_output);
					$('#urdf').text(response.val.urdf_output);
					$('#output').text("OUTPUT done!");
				}
			}
		});
    }); 
});