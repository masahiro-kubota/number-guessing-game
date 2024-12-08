function handleFormSubmit(event){
  event.preventDefault();
  console.log(event.type);
}

function main(){
  // inputNumFormのsubmitボタンが押されるとhanlerFormSubmitがイベントコールされる 
  // eventは送信されたeventオブジェクト
  document.getElementById("inputNumForm").addEventListener("submit", handleFormSubmit);
}

window.addEventListener("DOMContentLoaded", main);
