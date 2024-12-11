function handleFormSubmit(event){
  const secret_number = 100;
  event.preventDefault();
  const info = document.getElementById("info");
  const input_num  = document.getElementById("input_num").value;
  if (input_num == secret_number) {
    info.textContent = `${input_num} is secret number`;
  } else {
    info.textContent = `${input_num} is not secret number`;
  }
}

function main(){
  // inputNumFormのsubmitボタンが押されるとhanlerFormSubmitがイベントコールされる 
  // eventは送信されたeventオブジェクト
  let input_num = document.getElementById("inputNumForm").addEventListener("submit", handleFormSubmit);
}

window.addEventListener("DOMContentLoaded", main);
