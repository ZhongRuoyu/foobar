/* Copyright (c) 2020 Zhong Ruoyu. All rights reserved.  */

var numCount = 2;
document.addEventListener("keydown", keyCheck);
document.addEventListener("keydown", ctrlDetection);

function keyCheck(event) {
    if (
        document.activeElement.tagName == "INPUT" &&
        document.activeElement.className == "operation"
    ) {
        var keyID = event.keyCode;
        switch (keyID) {
            case 8:
                if (document.activeElement.value == "") {
                    event.preventDefault();
                    var index = parseInt(
                        document.activeElement.id.substring(3)
                    );
                    if (index > 1) {
                        remove(index);
                    }
                }
                break;
            case 13:
                event.preventDefault();
                var index = parseInt(document.activeElement.id.substring(3));
                add(index);
                break;
        }
    }
}

function ctrlDetection(e) {
    e = e || window.event;
    var key = e.which || e.keyCode; // keyCode detection
    var ctrl = e.ctrlKey ? e.ctrlKey : key === 17 ? true : false; // ctrl detection

    if (
        ctrl &&
        ((key == 67 &&
            document.getElementById("calculate").innerHTML ==
                "Calculate Sum (Ctrl + C)") ||
            (key == 73 &&
                document.getElementById("calculate").innerHTML ==
                    "Ignore (Ctrl + I)"))
    ) {
        event.preventDefault();
        document.getElementById("calculate").onclick();
    } else if (
        ctrl &&
        key == 76 &&
        document.getElementById("locate").style.display != "none"
    ) {
        event.preventDefault();
        locate();
    }
}

function insertAfter(referenceNode, newNode) {
    referenceNode.parentNode.insertBefore(newNode, referenceNode.nextSibling);
}

function add(index) {
    for (var i = numCount; i > index; i--) {
        document.getElementById("p" + i).id = "p" + (i + 1);
        document.getElementById("index" + i).innerHTML = i + 1;
        if (i + 1 < 10) {
            document.getElementById("index" + i).innerHTML += "&nbsp;&nbsp;";
        } else if (i + 1 < 100) {
            document.getElementById("index" + i).innerHTML += "&nbsp;";
        }
        document.getElementById("index" + i).id = "index" + (i + 1);
        document.getElementById("num" + i).id = "num" + (i + 1);
        document
            .getElementById("add" + i)
            .setAttribute("onclick", "add(" + (i + 1) + ")");
        document.getElementById("add" + i).id = "add" + (i + 1);
        document
            .getElementById("remove" + i)
            .setAttribute("onclick", "remove(" + (i + 1) + ")");
        document.getElementById("remove" + i).id = "remove" + (i + 1);
    }
    var newP = document.createElement("p");
    newP.id = "p" + (index + 1);
    var newSpan = document.createElement("span");
    newSpan.className = "operation";
    newSpan.id = "index" + (index + 1);
    newSpan.innerHTML = index + 1;
    if (index < 9) {
        newSpan.innerHTML += "&nbsp;&nbsp;";
    } else if (index < 99) {
        newSpan.innerHTML += "&nbsp;";
    }
    var newInput = document.createElement("input");
    newInput.className = "operation";
    newInput.type = "number";
    newInput.id = "num" + (index + 1);
    var newAdd = document.createElement("button");
    newAdd.className = "operation";
    newAdd.id = "add" + (index + 1);
    newAdd.setAttribute("onclick", "add(" + (index + 1) + ")");
    newAdd.innerHTML = "+";
    var newRemove = document.createElement("button");
    newRemove.className = "operation";
    newRemove.id = "remove" + (index + 1);
    newRemove.setAttribute("onclick", "remove(" + (index + 1) + ")");
    newRemove.innerHTML = "-";
    newP.appendChild(newSpan);
    newP.innerHTML += "&nbsp;";
    newP.appendChild(newInput);
    newP.innerHTML += "&nbsp;";
    newP.appendChild(newAdd);
    newP.innerHTML += "&nbsp;";
    newP.appendChild(newRemove);
    insertAfter(document.getElementById("p" + index), newP);
    numCount++;
    if (document.getElementById("remove1").getAttribute("disabled") != null) {
        document.getElementById("remove1").removeAttribute("disabled");
    }
    document.getElementById("num" + (index + 1)).focus();
}

function remove(index) {
    document.getElementById("p" + index).remove();
    for (var i = index + 1; i <= numCount; i++) {
        document.getElementById("p" + i).id = "p" + (i - 1);
        document.getElementById("index" + i).innerHTML = i - 1;
        if (i <= 10) {
            document.getElementById("index" + i).innerHTML += "&nbsp;&nbsp;";
        } else if (i <= 100) {
            document.getElementById("index" + i).innerHTML += "&nbsp;";
        }
        document.getElementById("index" + i).id = "index" + (i - 1);
        document.getElementById("num" + i).id = "num" + (i - 1);
        document
            .getElementById("add" + i)
            .setAttribute("onclick", "add(" + (i - 1) + ")");
        document.getElementById("add" + i).id = "add" + (i - 1);
        document
            .getElementById("remove" + i)
            .setAttribute("onclick", "remove(" + (i - 1) + ")");
        document.getElementById("remove" + i).id = "remove" + (i - 1);
    }
    numCount--;
    if (numCount == 1) {
        document.getElementById("remove1").setAttribute("disabled", "");
    }
    if (index > numCount) {
        document.getElementById("num" + (index - 1)).focus();
    } else {
        document.getElementById("num" + index).focus();
    }
}

function execute() {
    if (document.getElementById("calculate").innerHTML == "Ignore (Ctrl + I)") {
        sumCalc();
    } else {
        document.getElementById("calculate").innerHTML =
            "Calculate Sum (Ctrl + C)";
        for (let i = 1; i <= numCount; i++) {
            if (document.getElementById("num" + i).value == "") {
                document
                    .getElementById("result")
                    .setAttribute("value", "You have empty cells.");
                document.getElementById("locate").style.display =
                    "inline-block";
                document.getElementById("calculate").innerHTML =
                    "Ignore (Ctrl + I)";
                return 0;
            }
        }
        sumCalc();
    }
}

function locate() {
    for (let i = 1; i <= numCount; i++) {
        if (document.getElementById("num" + i).value == "") {
            document.getElementById("num" + i).focus();
            return 0;
        }
    }
    document
        .getElementById("result")
        .setAttribute("value", "Empty cells undetected.");
    document.getElementById("locate").style.display = "none";
    document.getElementById("calculate").innerHTML = "Calculate Sum (Ctrl + C)";
}

function sumCalc() {
    document.getElementById("locate").style.display = "none";
    let sum = 0;
    for (let i = 1; i <= numCount; i++) {
        if (document.getElementById("num" + i).value != "") {
            sum += parseFloat(document.getElementById("num" + i).value);
        } else {
            if (i != 1 || numCount != 1) {
                remove(i);
                i--;
            } else {
                document
                    .getElementById("result")
                    .setAttribute("value", "Please enter data first.");
                document.getElementById("calculate").innerHTML =
                    "Calculate Sum (Ctrl + C)";
                return 0;
            }
        }
    }
    document.getElementById("calculate").innerHTML = "Calculate Sum (Ctrl + C)";
    document.getElementById("result").setAttribute("value", sum);
}
