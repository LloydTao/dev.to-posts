## Your Intro to Stripe Payment Processing (Django)

### Introduction

Stripe is an online payments processor.

It's useful for any internet commerce; from online stores to subscriptions, and from marketplaces to crowdfunding.

It includes [Stripe Checkout](https://stripe.com/docs/payments/checkout) for almost instant integration.

### Features

Stripe is **elegant**. It abstracts most of the payments process. You don't need to worry about passing card details around and processing it yourself.

Stripe is **robust**. It can send dummy payments with test cards before completing a purchase flow.

Stripe is **secure**. AES-256 encryption is built in, with decryption keys stored separately.

Stripe is **compliant**. It has PCI, PSD2, SCA and SSAE18/SOC certifications, and has licenses globally.

### Fees

Stripe Payments charge 1.4% + 20p for European cards and 2.9% + 20p for non-European cards.

Stripe Billing, for recurring payments, charges 0.5%.

### Extensions

Stripe has a host of additional features:

- Stripe **Connect** for marketplaces with dedicated sellers, with a monthly fee per account.

- Strip **Radar** for machine learning fraud protection.

- Stripe **Sigma** for business reports powered by SQL.

- Stripe **Atlas** to launch a start-up (LLC, bank account, stock issuing) for a one-time fee.

## Setting Up

### Overview

Our tasks at hand are essentially:

1. Create a Stripe account and grab your API key.

2. Install the Stripe API (Python: `$ pip install stripe`).

3.  Add a Stripe form to the website 

    - Use Stripe's `checkout.js` to easily create the form.
	
	- Add your Stripe API key to the form.
	
    - Use cross-site request forgery protection (Django: `{% csrf_token %}`.
	
    - Stripe will validate the payment form before submitting it.

5. You can now view the payments on the Stripe dashboard.

### Example

A Django view using this code will look something like:

```html
<h1>Purchase hat:</h1>
<form action="{% url 'charge' %}" method="POST">
  {% csrf_token %}
  <script src="https://checkout.stripe.com/checkout.js" class="stripe-button"
          data-key="{{ key }}"
          data-description="You are purchasing: Hat."
          data-amount="100"
		  data-currency="GBP"
          data-locale="auto"></script>
</form>
```

![Pass by Reference vs. Pass by Value Analogy](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/002-Stripe-Form.png)




