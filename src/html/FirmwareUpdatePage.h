#ifndef ESP32OTAUPDATER_FIRMWARE_UPDATE_PAGE_H
#define ESP32OTAUPDATER_FIRMWARE_UPDATE_PAGE_H

#include <Arduino.h>

// Previously this page called onchange='sub(this)' and had an empty #prg
// div for progress, but no <script> tag anywhere defined sub() or updated
// #prg — the progress bar never actually did anything. This version submits
// the upload via XMLHttpRequest instead of a plain form POST specifically
// so upload progress (e.load/e.total) can be tracked and shown live.
const char FIRMWARE_UPDATE_PAGE_HTML[] PROGMEM = R"rawliteral(
<html><head><style>
%STYLE%
.form-container .center-content { text-align: center; }
.form-container input[type='file'] { display: none; }
.form-container label[for='file-input'] { display: inline-block; padding: 10px 20px; background-color: #0074D9; color: #fff; cursor: pointer; border-radius: 4px; }
.form-container .btn-container { text-align: center; }
#prg { margin-top: 10px; font-weight: bold; }
</style></head><body>
<h1>Firmware Update</h1>
<div class='form-container'>
<form id='upload_form' onsubmit='return uploadFirmware(event)'>
<div class='center-content'>
<br><label for='file-input' id='file-label'>Choose firmware file...</label>
<input type='file' name='update' id='file-input' onchange='updateFileLabel(this)'>
</div>
<div class='btn-container'>
<br><br><input type='submit' class='btn' value='Update'><br><br>
<div id='prg'></div>
</div>
</form></div>
<script>
function updateFileLabel(input) {
  var label = document.getElementById('file-label');
  label.innerHTML = input.files.length ? input.files[0].name : 'Choose firmware file...';
}

function uploadFirmware(event) {
  event.preventDefault();
  var fileInput = document.getElementById('file-input');
  var prg = document.getElementById('prg');

  if (!fileInput.files.length) {
    prg.innerHTML = 'Please choose a firmware file first.';
    return false;
  }

  var formData = new FormData();
  formData.append('update', fileInput.files[0]);

  var xhr = new XMLHttpRequest();
  xhr.open('POST', '/update', true);

  xhr.upload.onprogress = function (e) {
    if (e.lengthComputable) {
      var percent = Math.round((e.loaded / e.total) * 100);
      prg.innerHTML = 'Uploading: ' + percent + '%';
    }
  };

  xhr.onload = function () {
    if (xhr.status === 200 && xhr.responseText.indexOf('OK') !== -1) {
      prg.innerHTML = 'Update successful. Rebooting...';
    } else {
      prg.innerHTML = 'Update failed: ' + xhr.responseText;
    }
  };

  xhr.onerror = function () {
    prg.innerHTML = 'Upload failed (the device may already be rebooting).';
  };

  xhr.send(formData);
  return false;
}
</script>
</body></html>
)rawliteral";

#endif
