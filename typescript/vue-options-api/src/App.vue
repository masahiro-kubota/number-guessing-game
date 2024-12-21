<script lang='ts'>
import { ComparisonResult } from './enums/ComparisonResult';
import { numberInput } from './types/index';
import { GameLogic } from './logic/GameLogic';
import { LocalStorageGameStorage } from './logic/GameStorage'; 

export default {
  data(): {gameLogic: GameLogic | null, storage: LocalStorageGameStorage | null, reply: string, inputNum: number | null} {
    return {
      gameLogic: null,
      storage: null,
      reply: 'Enter a number',
      inputNum: null,
    }
  },
  mounted() {
    const secretNumber: number = 49;
    const maxCount: number = 7;
    this.storage = new LocalStorageGameStorage('my-game');
    this.gameLogic = new GameLogic(this.storage, secretNumber, maxCount);
  },
  methods: {
    handleSubmit() {
      console.log(this.secretNumber);
      this.reply = this.gameLogic.checkInput(this.inputNum);
      this.inpuNum = 0; 
    },
    handleReset() {
      console.log('test2');
      if (!this.gameLogic) return;
      this.gameLogic.restartGame();
      this.reply = 'Reset';
      this.inputNum = 0;
    }
  }
}

</script>

<template>
  <div class="flex flex-col items-center justify-center min-h-screen bg-gray-100 text-gray-900">
    <h1 class="text-3xl font-bold mb-4">Number Guessing Game</h1>
    <form @submit.prevent="handleSubmit" class="flex space-x-2 mb-4">
      <input
        v-model="inputNum"
        placeholder="e.g., 99"
        required
        class="border rounded px-2 py-1 text-lg"
      />
      <button
        type="submit"
        class="bg-blue-500 text-white px-3 py-1 rounded text-lg"
      >
        Submit
      </button>
    </form>
    <div class="mb-4">
      <p>{{ reply }}</p>
    </div>
    <button
      @click="handleReset"
      class="bg-blue-500 text-white px-3 py-1 rounded text-lg"
    >
      Reset
    </button>
  </div>
</template>
