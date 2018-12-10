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
function getwaterlvl(){
	var xhttp;
	xhttp=new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			serverresponse(this);
		}
	};
	xhttp.open("POST", "index.cgi", true);
	xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	xhttp.send("waterlvl");
}
function setwaterlvl(lvl){
	var waterlvl = lvl.split('=');
	if(waterlvl[1] == '0'){
		var element = document.getElementById("sysmode");
		if(e.options[e.selectedIndex].value != "standby"){
		confirm("System in standby mode because of low water level!");
		document.location.reload(true);
		}
	}
	else{
		document.getElementById("waterlvl").innerHTML = "There are approximately " + waterlvl[1] + " ml water in the tank";
	}
}
function serverresponse(xhttp) {
	if(xhttp.responseText.includes("waterlvl")){
		setwaterlvl(xhttp.responseText);
	}
	else{
		confirm(xhttp.responseText);
	}
}
setInterval(getwaterlvl, 60000);
