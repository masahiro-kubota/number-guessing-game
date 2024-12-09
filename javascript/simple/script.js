function handleFormSubmit(event){
  event.preventDefault();
  const input_num  = document.getElementById("input_num").value
  info.textContent = `Your answer is ${input_num}`;
}

function main(){
  // inputNumFormのsubmitボタンが押されるとhanlerFormSubmitがイベントコールされる 
  // eventは送信されたeventオブジェクト
  document.getElementById("inputNumForm").addEventListener("submit", handleFormSubmit);
}

window.addEventListener("DOMContentLoaded", main);
