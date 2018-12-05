function changesysmode() {
	var xhttp;
	var e = document.getElementById("sysmode");
	xhttp=new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
		if(this.responseText.includes("manual")){
			manual(true);
		}
		else{
			manual(false);
		}
		serverresponse(this);
		}
	};
	xhttp.open("POST", "index.cgi", true);
	xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	xhttp.send("sysmode=" + e.options[e.selectedIndex].value);
}
function changewatermode(mode){
	var xhttp;
	xhttp=new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			serverresponse(this);
		}
	};
	xhttp.open("POST", "index.cgi", true);
	xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	xhttp.send("watermode=" + mode);
}
function manualcontrol(control){
	var xhttp;
	xhttp=new XMLHttpRequest();
	xhttp.open("POST", "index.cgi", true);
	xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	xhttp.send("manualctl=" + control);
}
function serverresponse(xhttp) {
	confirm(xhttp.responseText);
}
function manual(enable){
	var element = document.getElementById("manualctn");
	if(enable){
		element.classList.remove("hide");
	}
	else{
		if(!element.classList.contains("hide")){
            element.classList.add("hide");
        }
	}
}
