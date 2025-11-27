document.querySelector(".to-menu-btn").addEventListener("click", () => {
    window.location.href = "/../puzzle-levels/";
})

PuzzleLevelsModule().then((Module) => {
    const getPuzzleCount      = Module.cwrap("getPuzzleLevelCount", "number", []);
    const getLevelNumber      = Module.cwrap("getPuzzleLevelNumber", "number", ["number"]);
    const getPuzzleLevelTitle = Module.cwrap("getPuzzleLevelTitle", "string", ["number"])
    const getPuzzleLevelSubtitle = Module.cwrap("getPuzzleLevelSubtitle", "string", ["number"]) 
    const getBitwidth         = Module.cwrap("getPuzzleLevelBitWidth", "number", []);
    const getStartBitstring   = Module.cwrap("getPuzzleLevelStartBitstring", "string", []);
    const getGoalBitstring    = Module.cwrap("getPuzzleLevelGoalBitstring", "string", []);
    const getOpCount          = Module.cwrap("getPuzzleLevelOpCount", "number", []);
    const getOperations       = Module.cwrap("getPuzzleLevelOperations", "string", []);
    const getDesc             = Module.cwrap("getPuzzleLevelDescription", "string", []);


    const title         = document.querySelector(".title");
    const subtitle      = document.querySelector(".subtitle");
    const currentBit    = document.querySelector(".current-bitstring-screen");
    const targetBit     = document.querySelector(".target-section .bitstring");
    const opcount       = document.querySelector(".operation-count-section .screen")
    const opButtons     = document.querySelector(".main-buttons");
    const desc          = document.querySelector(".body");

    const params = new URLSearchParams(document.location.search);
    const puzzleIndex = parseInt(params.get("level"));
    const puzzleUnlockedLevels = JSON.parse(sessionStorage.getItem("unlockedLevels"));

    console.log(getPuzzleLevelTitle(puzzleIndex));

    title.textContent       = getPuzzleLevelTitle(puzzleIndex);
    subtitle.textContent    = getPuzzleLevelSubtitle(puzzleIndex);
    currentBit.textContent  = getStartBitstring(puzzleIndex); 
    targetBit.textContent   = getGoalBitstring(puzzleIndex);
    opcount.textContent     = getOpCount(puzzleIndex);
    desc.innerHTML        = getDesc(puzzleIndex)

    function unlockNextLevel(currentLevel) {
        const nextLevel = currentLevel + 1;
        const unlockedLevels = JSON.parse(sessionStorage.getItem("unlockedLevels"));
        if (!unlockedLevels.includes(nextLevel) && nextLevel <= getPuzzleCount()) {
            sessionStorage.setItem("unlockedLevels", JSON.stringify([...unlockedLevels, nextLevel]));
            console.log("Level " + nextLevel + " has been unlocked.");
        }
    }

    if (!puzzleUnlockedLevels.includes(puzzleIndex + 1)) {
        window.location.href = "./../puzzle-levels/"
    } else {
        document.querySelector("main").classList.remove("hidden");
    }

    GameLogicModule().then((Module) => { 
        const doBitOperation = Module.cwrap(
            "bitStringOperations", "string", ["string", "string", "string", "number"]
        );

        const operations = getOperations(puzzleIndex).split(",");
        operations.forEach(op => {
            const button = document.createElement("button");
            button.className = "operation-btn";
            button.textContent = op;

            let [operation, operand] = op.split(" ");
            if (operand === undefined) operand = "";

            button.addEventListener("click", () => { 
                currentBit.textContent = doBitOperation(
                    currentBit.textContent, 
                    operand,
                    operation,
                    getBitwidth(puzzleIndex)
                );
                opcount.textContent = parseInt(opcount.textContent) - 1;
                if (currentBit.textContent == targetBit.textContent) {
                    const modalOverlay = document.querySelector(".modal-overlay");
                    const victoryModal = document.querySelector(".victory-modal");
                    modalOverlay.classList.remove("hidden");
                    victoryModal.classList.remove("hidden");
                    unlockNextLevel(puzzleIndex + 1);
                } else if (opcount.textContent == 0) {
                    const modalOverlay = document.querySelector(".modal-overlay");
                    const gameOverModal = document.querySelector(".gameover-modal");
                    modalOverlay.classList.remove("hidden");
                    gameOverModal.classList.remove("hidden");                    
                }
            });

            opButtons.appendChild(button);
        });        
    });

    const resetLevel = document.querySelectorAll(".reset-btn");
    resetLevel.forEach(btn => {
        btn.addEventListener("click", () => {
            window.location.reload();
        });
    })  

    const toPuzzlePage = document.querySelectorAll(".to-puzzle-btn");
    toPuzzlePage.forEach(btn => {
        btn.addEventListener("click", () => {
            window.location.href = "./../puzzle-levels/"
        });
    })

    const nextPuzzleBtn = document.querySelector(".next-puzzle-btn");
    nextPuzzleBtn.addEventListener("click", () => {
        window.location.href = `./../puzzle/?level=${puzzleIndex + 1}`;
    });
});


