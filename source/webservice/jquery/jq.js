$( document ).ready(function() {
    $("#make").click(function(){ 
		var param = $('#param').val();
		var challange = $('#challange').val();
		$('#output').text('Please wait a moment!');
		$.post("compiling.php",{param: param, challange: challange}, function(data){
			$('#output').text(data);
		});
    }); 
});