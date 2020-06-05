## Your Intro to Stripe (Django)

### Introduction

Stripe is an online payments processor.

It's incredible useful for almost any internet commerce; from online stores to subscriptions, and from user-driven marketplaces to crowdfunding.

This guide will briefly overview Stripe and its API, and give examples on how to integrate it with Django.

*If you're using a different framework, it should be easily adaptable!*

### Features

Stripe is **elegant**. It abstracts most of the payments process. You don't need to worry about passing card details around and processing it yourself.

Stripe is **robust**. It can send dummy payments with test cards before completing a purchase flow.

Stripe is **secure**. AES-256 encryption is built in, with decryption keys stored separately.

Stripe is **compliant**. This includes PCI, PSD2, SCA and SSAE18/SOC certifications.

![Stripe Compliance Certifications](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/000-Stripe-Compliant.png)

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

3. Add Stripe to the frontend (we're using `checkout.js`).

4. We're done! View processed payments on your Stripe account.

### Creating a Stripe Account

Head to https://dashboard.stripe.com/register to create an account.

![Registering a Stripe Account](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/001-Stripe-Account.png)

Remember to verify your account:

![Verifying a Stripe Account](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/002-Stripe-Verify.png)

Now, grab your public API key:

![Getting a Stripe API Key](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/003-Stripe-Key.png)

### Installing the Stripe API

Make sure you've set up your project, virtual environment and requirements. [Here's a Django guide](https://dev.to/tao/your-intro-to-django-2020-3a01).

Add Stripe to your `requirements.txt` for pip. You'll probably want the latest version.

![Adding Stripe to Requirements](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/004-Django-Requirements.png)

Install with `pip install -r requirements.txt`.

### Adding Stripe to the Frontend

Using Stripe Checkout, we can create a payment form (and handle it) incredibly quickly.

**Product Page**

To create a form, the Django template will look something like this:

```html
<h1>Purchase hat:</h1>
<form action="{% url 'payments-charge' %}" method="POST">
  {% csrf_token %}
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


