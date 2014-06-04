$( document ).ready(function() {
    $("#make").click(function(){ 
		var param = $('#param').val();
		var challange = $('#challange').val();
		$('#output').text('Please wait a moment!');
		$.post("compiling.php",{param: param, challange: challange}, function(data){
			var response = jQuery.parseJSON(data);
			if(typeof response =='object'){
				$('#grid').text(response[0]);
			}else{
				$('#output').text(data);
			}
		});
    }); 
});