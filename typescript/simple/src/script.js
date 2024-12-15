var __classPrivateFieldSet = (this && this.__classPrivateFieldSet) || function (receiver, state, value, kind, f) {
    if (kind === "m") throw new TypeError("Private method is not writable");
    if (kind === "a" && !f) throw new TypeError("Private accessor was defined without a setter");
    if (typeof state === "function" ? receiver !== state || !f : !state.has(receiver)) throw new TypeError("Cannot write private member to an object whose class did not declare it");
    return (kind === "a" ? f.call(receiver, value) : f ? f.value = value : state.set(receiver, value)), value;
};
var __classPrivateFieldGet = (this && this.__classPrivateFieldGet) || function (receiver, state, kind, f) {
    if (kind === "a" && !f) throw new TypeError("Private accessor was defined without a getter");
    if (typeof state === "function" ? receiver !== state || !f : !state.has(receiver)) throw new TypeError("Cannot read private member from an object whose class did not declare it");
    return kind === "m" ? f : kind === "a" ? f.call(receiver) : f ? f.value : state.get(receiver);
};
var _LocalStorageGameStorage_storageKey, _GameDomService_info, _GameDomService_inputNum, _GameDomService_inputNumForm, _GameDomService_resetButton, _GameLogic_secretNumber, _GameLogic_storage, _GameLogic_gameData, _GameLogic_maxCount, _GameUIAdapter_logic, _GameUIAdapter_domService;
// データの永続化 localStorageはweb APIで定義されているグローバルオブジェクト
var LocalStorageGameStorage = /** @class */ (function () {
    function LocalStorageGameStorage(storageKey) {
        if (storageKey === void 0) { storageKey = 'my-game'; }
        _LocalStorageGameStorage_storageKey.set(this, void 0);
        __classPrivateFieldSet(this, _LocalStorageGameStorage_storageKey, storageKey, "f");
    }
    LocalStorageGameStorage.prototype.save = function (data) {
        localStorage.setItem(__classPrivateFieldGet(this, _LocalStorageGameStorage_storageKey, "f"), JSON.stringify(data));
    };
    LocalStorageGameStorage.prototype.load = function () {
        var data = localStorage.getItem(__classPrivateFieldGet(this, _LocalStorageGameStorage_storageKey, "f"));
        return data ? JSON.parse(data) : [];
    };
    LocalStorageGameStorage.prototype.getCount = function () {
        return localStorage.getItem(this.storageKey, 'count');
    };
    LocalStorageGameStorage.prototype.resetGame = function () {
        localStorage.removeItem(__classPrivateFieldGet(this, _LocalStorageGameStorage_storageKey, "f"));
    };
    return LocalStorageGameStorage;
}());
_LocalStorageGameStorage_storageKey = new WeakMap();
// DOM操作の抽象化を行う
var GameDomService = /** @class */ (function () {
    function GameDomService() {
        _GameDomService_info.set(this, void 0);
        _GameDomService_inputNum.set(this, void 0);
        _GameDomService_inputNumForm.set(this, void 0);
        _GameDomService_resetButton.set(this, void 0);
        __classPrivateFieldSet(this, _GameDomService_info, document.getElementById('info'), "f");
        __classPrivateFieldSet(this, _GameDomService_inputNum, document.getElementById('input_num'), "f");
        __classPrivateFieldSet(this, _GameDomService_inputNumForm, document.getElementById('inputNumForm'), "f");
        __classPrivateFieldSet(this, _GameDomService_resetButton, document.getElementById('resetButton'), "f");
    }
    GameDomService.prototype.getInputNum = function () {
        return Number(__classPrivateFieldGet(this, _GameDomService_inputNum, "f").value);
    };
    GameDomService.prototype.setInputNum = function (value) {
        __classPrivateFieldGet(this, _GameDomService_inputNum, "f").value = value;
    };
    GameDomService.prototype.setReply = function (reply) {
        __classPrivateFieldGet(this, _GameDomService_info, "f").textContent = reply;
    };
    GameDomService.prototype.setAddInputListener = function (callback) {
        __classPrivateFieldGet(this, _GameDomService_inputNumForm, "f").addEventListener('submit', callback);
    };
    GameDomService.prototype.setAddResetListener = function (callback) {
        __classPrivateFieldGet(this, _GameDomService_resetButton, "f").addEventListener('click', callback);
    };
    return GameDomService;
}());
_GameDomService_info = new WeakMap(), _GameDomService_inputNum = new WeakMap(), _GameDomService_inputNumForm = new WeakMap(), _GameDomService_resetButton = new WeakMap();
// 状態管理やロジックを管理する一番核となる部分。異なるUIの場合でもここは変わらないようにする
var GameLogic = /** @class */ (function () {
    function GameLogic(storage, secretNumber, maxCount) {
        _GameLogic_secretNumber.set(this, void 0);
        _GameLogic_storage.set(this, void 0);
        _GameLogic_gameData.set(this, void 0);
        _GameLogic_maxCount.set(this, void 0);
        __classPrivateFieldSet(this, _GameLogic_secretNumber, secretNumber, "f");
        __classPrivateFieldSet(this, _GameLogic_storage, storage, "f");
        __classPrivateFieldSet(this, _GameLogic_gameData, __classPrivateFieldGet(this, _GameLogic_storage, "f").load(), "f");
        __classPrivateFieldSet(this, _GameLogic_maxCount, maxCount, "f");
    }
    GameLogic.prototype.restartGame = function () {
        __classPrivateFieldGet(this, _GameLogic_storage, "f").resetGame();
        __classPrivateFieldSet(this, _GameLogic_gameData, __classPrivateFieldGet(this, _GameLogic_storage, "f").load(), "f");
    };
    GameLogic.prototype.getLastNumber = function () {
        return __classPrivateFieldGet(this, _GameLogic_gameData, "f")[__classPrivateFieldGet(this, _GameLogic_gameData, "f").length - 1].number;
    };
    GameLogic.prototype.isMaxCount = function (count) {
        return (__classPrivateFieldGet(this, _GameLogic_maxCount, "f") === count) ? true : false;
    };
    GameLogic.prototype.isNumCorrect = function (number) {
        return (__classPrivateFieldGet(this, _GameLogic_secretNumber, "f") === number) ? true : false;
    };
    GameLogic.prototype.appendNumber = function (number) {
        var data = {
            'number': number
        };
        __classPrivateFieldGet(this, _GameLogic_gameData, "f").push(data);
        __classPrivateFieldGet(this, _GameLogic_storage, "f").save(__classPrivateFieldGet(this, _GameLogic_gameData, "f"));
    };
    GameLogic.prototype.relativeDistance = function (number) {
        var previousNumber = this.getLastNumber();
        var previousDistance = Math.abs(__classPrivateFieldGet(this, _GameLogic_secretNumber, "f") - previousNumber);
        var latestDistance = Math.abs(__classPrivateFieldGet(this, _GameLogic_secretNumber, "f") - number);
        return previousDistance === latestDistance
            ? ComparisonResult.NOTCHANGE
            : previousDistance > latestDistance
                ? ComparisonResult.CLOSER
                : ComparisonResult.FARTHER;
    };
    GameLogic.prototype.checkInput = function (input) {
        var count = __classPrivateFieldGet(this, _GameLogic_gameData, "f").length;
        if (isNaN(input)) {
            return "Your input is not Number. Count is ".concat(count);
        }
        var number = Number(input);
        if (number < 1 || 100 < number) {
            return "You need to input the number from 1 to 100. Count is ".concat(count);
        }
        if (this.isNumCorrect(number)) {
            this.restartGame();
            return "".concat(__classPrivateFieldGet(this, _GameLogic_secretNumber, "f"), " is the secret number. Count is ").concat(count + 1);
        }
        if (this.isMaxCount(count + 1)) {
            this.restartGame();
            return "The max attempts has been reached. Secret Number is ".concat(__classPrivateFieldGet(this, _GameLogic_secretNumber, "f"));
        }
        var relativeDistanceReply;
        if (count === 0) {
            relativeDistanceReply = "";
        }
        else {
            relativeDistanceReply = (this.relativeDistance(number) === ComparisonResult.NOTCHANGE)
                ? 'Equal Distance!'
                : (this.relativeDistance(number) === ComparisonResult.CLOSER)
                    ? 'Closer!'
                    : 'Farther!';
        }
        this.appendNumber(number);
        if (number < __classPrivateFieldGet(this, _GameLogic_secretNumber, "f")) {
            return "".concat(relativeDistanceReply, " Go higher! Count is ").concat(count + 1);
        }
        else if (number > __classPrivateFieldGet(this, _GameLogic_secretNumber, "f")) {
            return "".concat(relativeDistanceReply, " Go smaller! Count is ").concat(count + 1);
        }
    };
    return GameLogic;
}());
_GameLogic_secretNumber = new WeakMap(), _GameLogic_storage = new WeakMap(), _GameLogic_gameData = new WeakMap(), _GameLogic_maxCount = new WeakMap();
var ComparisonResult = /** @class */ (function () {
    function ComparisonResult() {
    }
    ComparisonResult.CLOSER = -1;
    ComparisonResult.NOTCHANGE = 0;
    ComparisonResult.FARTHER = 1;
    return ComparisonResult;
}());
// 抽象化されたUIのイベントにロジックを割り当てるアダプター。
var GameUIAdapter = /** @class */ (function () {
    function GameUIAdapter(logic, domService) {
        var _this = this;
        _GameUIAdapter_logic.set(this, void 0);
        _GameUIAdapter_domService.set(this, void 0);
        __classPrivateFieldSet(this, _GameUIAdapter_logic, logic, "f");
        __classPrivateFieldSet(this, _GameUIAdapter_domService, domService, "f");
        __classPrivateFieldGet(this, _GameUIAdapter_domService, "f").setAddInputListener(function () {
            event.preventDefault();
            var input = __classPrivateFieldGet(_this, _GameUIAdapter_domService, "f").getInputNum();
            var reply = __classPrivateFieldGet(_this, _GameUIAdapter_logic, "f").checkInput(input);
            __classPrivateFieldGet(_this, _GameUIAdapter_domService, "f").setReply(reply);
            __classPrivateFieldGet(_this, _GameUIAdapter_domService, "f").setInputNum('');
        });
        __classPrivateFieldGet(this, _GameUIAdapter_domService, "f").setAddResetListener(function () {
            __classPrivateFieldGet(_this, _GameUIAdapter_logic, "f").restartGame();
            __classPrivateFieldGet(_this, _GameUIAdapter_domService, "f").setReply('Reset');
            __classPrivateFieldGet(_this, _GameUIAdapter_domService, "f").setInputNum('');
        });
    }
    return GameUIAdapter;
}());
_GameUIAdapter_logic = new WeakMap(), _GameUIAdapter_domService = new WeakMap();
// アプリケーションの初期化と依存性注入(Dependency Injection)
var GameApp = /** @class */ (function () {
    function GameApp() {
    }
    GameApp.initialize = function () {
        var secretNumber = 49;
        var maxCount = 7;
        var storage = new LocalStorageGameStorage('my-game');
        var domService = new GameDomService();
        var gameLogic = new GameLogic(storage, secretNumber, maxCount);
        var gameUIAdapter = new GameUIAdapter(gameLogic, domService);
        return {
            logic: gameLogic,
            adapter: gameUIAdapter
        };
    };
    return GameApp;
}());
var app = GameApp.initialize();
