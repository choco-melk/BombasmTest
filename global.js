let currentEffect = null;

export default function addTypeWriterEffect(selector, content, skipby = 1, delayInMS = 50) {
    if (currentEffect) currentEffect.cancel = true;
    
    const effect = { cancel: false };
    currentEffect = effect;

    return new Promise(resolve => {
        let char = 0;
        const dest = document.querySelector(selector);

        function type() {
            if (effect.cancel) return resolve(); 

            dest.textContent = content.slice(0, char) + "_";

            if (char < content.length) {
                char++;
                setTimeout(type, delayInMS);
            } else {
                dest.textContent = content;
                resolve();
            }
        }

        type();
    });
}