$( document ).ready(function() {
	function scroll(aid){
	    var aTag = $(aid);
	    $('html,body').animate({scrollTop: aTag.offset().top},'slow');
	}
	function load(button, filename, data){
		Downloadify.create(button,{
			filename: function(){
				return filename;
			},
			data: function(){ 
				return document.getElementById(data).value;
			},
			onComplete: function(){ alert('The XML has been saved!'); },
			onCancel: function(){ console.log("canceled"); },
			onError: function(){ console.log("nothing"); },
			swf: 'downloadify/media/downloadify.swf',
			downloadImage: 'downloadify/images/download.png',
			width: 27,
			height: 30,
			transparent: false,
			append: false
		});
	}
	function SelectText(element) {
	    var text = document.getElementById(element);
	    if ($.browser.msie) {
	        var range = document.body.createTextRange();
	        range.moveToElementText(text);
	        range.select();
	    } else if ($.browser.mozilla || $.browser.opera) {
	        var selection = window.getSelection();
	        var range = document.createRange();
	        range.selectNodeContents(text);
	        selection.removeAllRanges();
	        selection.addRange(range);
	    } else if ($.browser.safari) {
	        var selection = window.getSelection();
	        selection.setBaseAndExtent(text, 0, text, 1);
	    }
	}
	$("[rel=select]").click(function() {
    	SelectText($(this));
  	});
    $("#make").click(function(){ 
		var param = $('#param').val();
		var challenge = $('#challenge').val();
		$('#output').text('Please wait a moment!');
		$.post("api/",{param: param, challenge: challenge}, function(data){
			var response = jQuery.parseJSON(data);
			if(typeof response =='object'){
				if(response.response_type=="error"){
					$('#output').text(response.val);
  					$('#output_div').fadeOut("fast");
				}else if(response.response_type=="ok"){
					$('#grid').text(response.val.grid_xml_output);
					$('#lab').text(response.val.lab_xml_output);
					$('#param_output').text(response.val.param_xml_output);
					$('#urdf_xml_output_rotate').text(response.val.urdf_xml_output_rotate);
					$('#urdf_xml_output_fixed').text(response.val.urdf_xml_output_fixed);
					$('#output').text("OUTPUT done!");
  					$('#output_div').fadeIn("fast");
  					load("grid_save_as", "GRID.xml", "grid");
  					load("lab_save_as", "LAB.xml", "lab");
  					load("param_output_save_as", "PARAM.xml", "param_output");
  					load("urdf_xml_output_rotate_save_as", "URDFRotate.xml", "urdf_xml_output_rotate");
  					load("urdf_xml_output_fixed_save_as", "URDFFixed.xml", "urdf_xml_output_fixed");
  					scroll('#output_div');
				}
			}
		});
    }); 
});