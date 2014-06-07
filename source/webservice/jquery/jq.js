$( document ).ready(function() {
	function scroll(aid){
	    var aTag = $(aid);
	    $('html,body').animate({scrollTop: aTag.offset().top},'slow');
	}
    $("#make").click(function(){ 
		var param = $('#param').val();
		var challange = $('#challange').val();
		$('#output').text('Please wait a moment!');
		$.post("api/",{param: param, challange: challange}, function(data){
			var response = jQuery.parseJSON(data);
			if(typeof response =='object'){
				if(response.response_type=="error"){
					$('#output').text(response.val);
  					$('#output_div').fadeOut("fast");
				}else if(response.response_type=="ok"){
					$('#grid').text(response.val.grid_output);
					$('#lab').text(response.val.lab_output);
					$('#param_output').text(response.val.param_output);
					$('#urdf_xml_output_rotate').text(response.val.urdf_xml_output_rotate);
					$('#urdf_xml_output_fixed').text(response.val.urdf_xml_output_fixed);
					$('#output').text("OUTPUT done!");
  					$('#output_div').fadeIn("fast");
  					scroll('#output_div');
				}
			}
		});
    }); 
});