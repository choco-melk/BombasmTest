import addTypeWriterEffect from './global.js'

(async () => {
    await addTypeWriterEffect(".desc", "BOMBASM is a web game built for people who want to learn more about bit manipulation and operations.", 4, 50)
}) ()

document.querySelector(".start-btn").addEventListener("click", e => {
    e.preventDefault();
    window.location.href = "./puzzle-levels/index.html"
})
