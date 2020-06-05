## Your Intro to Stripe Payment Processing (Django)

### Introduction

Stripe is an online payments processor.

It's useful for any internet commerce; from online stores to subscriptions, and from marketplaces to crowdfunding.

### Features

Stripe is **elegant**. It abstracts most of the payments process. You don't need to worry about passing card details around and processing it yourself.

Stripe is **robust**. It can send dummy payments with test cards before completing a purchase flow.

Stripe is **secure**. AES-256 encryption is built in, with decryption keys stored separately.

Stripe is **compliant**. It has PCI, PSD2, SCA and SSAE18/SOC certifications, and has licenses globally.

### Fees

Stripe **Payments** charge 1.4% + 20p for European cards and 2.9% + 20p for non-European cards.

Stripe **Billing**, used for recurring payments, charges 0.5%.

### Extensions

Stripe has a host of additional features:

- Stripe **Connect** for marketplaces with dedicated sellers, with a monthly fee per account.

- Stripe **Radar** for machine learning fraud protection.

- Stripe **Sigma** for business reports powered by SQL.

- Stripe **Atlas** to launch a start-up (LLC, bank account, stock issuing) for a one-time fee.

We'll be taking advantage of [Stripe Checkout](https://stripe.com/docs/payments/checkout) for quick and compliant integration.

## Setting Up

### Overview

Our tasks at hand are essentially:

1. Create a Stripe account and grab your API key.

2. Install the Stripe API for the backend (Python: `$ pip install stripe`).

3. Add Stripe to the front-end (we're using `checkout.js`).

4. We're done! View processed payments on your Stripe account.

### Creating a Stripe Account

Head to https://dashboard.stripe.com/register to create an account.

![Registering a Stripe Account](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/003-Stripe-Account.png)

### Example

A Django template will look something like:

```html
<h1>Purchase hat:</h1>
<form action="{% url 'charge' %}" method="POST">
  <script src="https://checkout.stripe.com/checkout.js" class="stripe-button"
          data-key="{{ key }}"
          data-description="You are purchasing: Hat."
          data-amount="100"
          data-currency="GBP"
          data-locale="auto">
  </script>
</form>
```

The resulting page looks like:

![Example Stripe Form](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/002-Stripe-Form.png)

Stripe will validate the payment form before submitting it.


