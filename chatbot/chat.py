import gradio as gr
from nltk.chat.util import Chat, reflections

books = {
    'fiction': ["The Alchemist", "1984", "The Great Gatsby"],
    'non-fiction': ["Sapiens", "Atomic Habits", "Educated"],
    'academic': ["Engineering Mathematics", "Human Anatomy", "Principles of Management"]
}

raw_patterns = {
    "hi|hello|hey": [
        "Hello! Welcome to BookWorld 📚. How can I assist you today?",
        "Hey there! Need help with books or orders?",
        "Hi! Looking for something to read?"
    ],
    "how are you": [
        "I'm just a bot, but I'm here to help you find the perfect book!"
    ],
    "book": [
        "We have fiction, non-fiction, and academic books. What are you looking for?"
    ],
    "fiction": [
        f"Our fiction section includes: {', '.join(books['fiction'])}. Would you like to buy one?"
    ],
    "non[- ]fiction": [
        f"Our non-fiction books include: {', '.join(books['non-fiction'])}. Would you like to buy one?"
    ],
    "academic": [
        f"Our academic books include: {', '.join(books['academic'])}. Interested in purchasing?"
    ],
    "price|cost": [
        "Most books range from ₹200 to ₹1500 depending on the category and author."
    ],
    "buy|order": [
        "Great! Let’s proceed with your order. Type 'start order' to begin."
    ],
    "help": [
        "I can assist you with book categories, prices, and placing orders."
    ],
    "contact": [
        "You can email us at support@bookworld.com or call 1800-BOOK-123."
    ],
    "bye|goodbye|exit": [
        "Thank you for visiting BookWorld! 📖 Goodbye!"
    ],
    "yes|yeah|yep": [
        "Great! Let's proceed with your order. Type 'start order' to begin."
    ]
}

patterns = [(rf"(.*){key}(.*)", value) for key, value in raw_patterns.items()]


chatbot = Chat(patterns, reflections)
session = {"order_mode": False, "step": 0}

def respond(message, history):
    message = message.strip().lower()

    if session["order_mode"]:
        step = session["step"]
        return globals()[f"step_{step}"](message)

    if "start order" in message:
        session["order_mode"] = True
        session["step"] = 0
        return "Ok let's start. Which category book (fiction/non-fiction/academic)?"

    reply = chatbot.respond(message)
    return reply if reply else "Sorry. I love you."

def step_0(message):
    if message not in books:
        return "Category not found 404"
    session["step"] = 1
    return f"You selected {message} category. We have {', '.join(books[message])} books for this category. Which one would you like to buy? You can also type 'nothing' if you would like to exit"

def step_1(message):
    if message == 'nothing':
        session["order_mode"] = False
        session["step"] = 0
        return "Thank you for chatting"
    session["step"] = 2
    return f"{message} added to cart. Cost is Rs.500. Should I confirm the order? (yes/no)"

def step_2(message):
    session["order_mode"] = False
    session["step"] = 0
    return "Order confirmed. Will reach soon." if message == 'yes' else "No worries! Come back later."

demo = gr.ChatInterface(
    fn=respond,
    title="📚 BookWorld Chatbot",
    description="Ask me about books, prices, or place an order!",
    theme="soft"
)

demo.launch()
